#include<vector>
#include<memory>
/*
⼀个尤其令⼈意外的地⽅是使⽤this原始指针作为std::shared_ptr构造函数实参的时候可能导致创建
多个控制块。假设我们的程序使⽤std::shared_ptr管理Widget对象，我们有⼀个数据结构⽤于跟踪
已经处理过的Widget对象：
*/
// class Widget{
// public:
//     void process();
// };
// void Widget::process(){
//     processedWidgets.emplace_back(this);//然后将他加到已处理过的Widget的列表中 这时错的
// }
/*
评论已经说了这是错的——或者⾄少⼤部分是错的。（错误的部分是传递this，而不是使⽤了
emplace_back。如果你不熟悉emplace_back，参⻅Item42）。上⾯的代码可以通过编译，但是向容
器传递⼀个原始指针（this），std::shared_ptr会由此为指向的对象（*this）创建⼀个控制块。那
看起来没什么问题，直到你意识到如果成员函数外⾯早已存在指向Widget对象的指针，它是未定义⾏为
的Game, Set, and Match（译注：⼀部电影，但是译者没看过。。。）。
std::shared_ptr API已有处理这种情况的设施。它的名字可能是C++标准库中最奇怪的⼀个：
std::enable_shared_from_this。它是⼀个⽤做基类的模板类，模板类型参数是某个想被
std::shared_ptr管理且能从该类型的this对象上安全创建std::shared_ptr指针的存在。在我们的
例⼦中，Widget将会继承⾃std::enable_shared_from_this：
*/
class Widget:public std::enable_shared_from_this<Widget>{
public:
    void process();
};
std::vector<std::shared_ptr<Widget>> processedWidgets;//processedWidgets.push_back();这个就和上面的一样的重复创建控件快，导致多次释放的危险
/*
正如我所说，std::enable_shared_from_this是⼀个⽤作基类的模板类。它的模板参数总是某个继
承⾃它的类，所以Widget继承⾃std::enable_shared_from_this<Widget>。如果某类型继承⾃⼀个
由该类型（译注：作为模板类型参数）进⾏模板化得到的基类这个东西让你⼼脏有点遭不住，别去想它
就好了。代码完全合法，而且它背后的设计模式也是没问题的，并且这种设计模式还有个标准名字，尽
管该名字和std::enable_shared_from_this⼀样怪异。这个标准名字就是奇异递归模板模式（The
Curiously Recurring Template Pattern(CRTP))。如果你想学更多关于它的内容，请搜索引擎⼀展⾝
⼿，现在我们要回到std::enable_shared_from_this上。
std::enable_shared_from_this定义了⼀个成员函数，成员函数会创建指向当前对象的
std::shared_ptr却不创建多余控制块。这个成员函数就是shared_from_this，⽆论在哪当你想使
⽤std::shared_ptr指向this所指对象时都请使⽤它。这⾥有个Widget::process的安全实现：


*/
void Widget::process(){
    processedWidgets.emplace_back(shared_from_this());//这个函数就不会创建多余的控制块 ，每个对象就会释放一次
}
/*
从内部来说，shared_from_this查找当前对象控制块，然后创建⼀个新的std::shared_ptr指向这
个控制块。设计的依据是当前对象已经存在⼀个关联的控制块。要想符合设计依据的情况，必须已经存
在⼀个指向当前对象的std::shared_ptr (即调⽤shared_from_this的成员函数外⾯已经存在⼀个
std::shared_ptr )。如果没有std::shared_ptr指向当前对象（即当前对象没有关联控制块），⾏为
是未定义的，shared_from_this通常抛出⼀个异常。
要想防⽌客⼾端在调⽤std::shared_ptr前先调⽤shared_from_this，继承⾃
std::enable_shared_from_this的类通常将它们的构造函数声明为private，并且让客⼾端通过⼯⼚
⽅法创建std::shared_ptr


*/
class Widget: public std::enable_shared_from_this<Widget> {
public:
// 完美转发参数的⼯⼚⽅法
template<typename... Ts>
static std::shared_ptr<Widget> create(Ts&&... params);

void process(); // 和前⾯⼀样

private:
};
/*
现在，你可能隐约记得我们讨论控制块的动机是想了解std::shared_ptr关联⼀个控制块的成本。既然
我们已经知道了怎么避免创建过多控制块，就让我们回到原来的主题。
控制块通常只占⼏个word⼤小，⾃定义销毁器和分配器可能会让它变⼤⼀点。通常控制块的实现⽐你想
的更复杂⼀些。它使⽤继承，甚⾄⾥⾯还有⼀个虚函数（⽤来确保指向的对象被正确销毁）。这意味着
使⽤std::shared_ptr还会招致控制块使⽤虚函数带来的成本。
了解了动态分配控制块，任意⼤小的销毁器和分配器，虚函数机制，原⼦引⽤计数修改，你对于
std::shared_ptr的热情可能有点消退。可以理解，对每个资源管理问题来说都没有最佳的解决⽅案。
但就它提供的功能来说，std::shared_ptr的开销是⾮常合理的。在通常情况下，std::shared_ptr
创建控制块会使⽤默认销毁器和默认分配器，控制块只需三个word⼤小。它的分配基本上是⽆开销的。
（开销被并⼊了指向的对象的分配成本⾥。细节参⻅Item21）。对std::shared_ptr解引⽤的开销不
会⽐原始指针⾼。执⾏原⼦引⽤计数修改操作需要承担⼀两个原⼦操作开销，这些操作通常都会⼀⼀映
射到机器指令上，所以即使对⽐⾮原⼦指令来说，原⼦指令开销较⼤，但是它们仍然只是单个指令。对
于每个被std::shared_ptr指向的对象来说，控制块中的虚函数机制产⽣的开销通常只需要承受⼀次，
即对象销毁的时候。
作为这些轻微开销的交换，你得到了动态分配的资源的⽣命周期⾃动管理的好处。⼤多数时候，⽐起⼿
动管理，使⽤std::shared_ptr管理共享性资源都是⾮常合适的。如果你还在犹豫是否能承受
std::shared_ptr带来的开销，那就再想想你是否需要共享资源。如果独占资源可⾏或者可能可⾏，
⽤std::unique_ptr是⼀个更好的选择。它的性能profile更接近于原始指针，并且从
std::unique_ptr升级到std::shared_ptr也很容易，因为std::shared_ptr可以从
std::unique_ptr上创建。
反之不⾏。当你的资源由std::shared_ptr管理，现在⼜想修改资源⽣命周期管理⽅式是没有办法的。
即使引⽤计数为⼀，你也不能重新修改资源所有权，改⽤std::unique_ptr管理它。所有权和
std::shared_ptr指向的资源之前签订的协议是“除⾮死亡否则永不分离”。不能离婚，不能废除，没有
特许。
std::shared_ptr不能处理的另⼀个东西是数组。和std::unique_ptr不同的是，
std::shared_ptr的API设计之初就是针对单个对象的，没有办法std::shared_ptr<T[]>。⼀次⼜⼀
次，“聪明”的程序员踌躇于是否该使⽤std::shared_ptr<T>指向数组，然后传⼊⾃定义数组销毁器。
（即delete []）。这可以通过编译，但是是⼀个糟糕的注意。⼀⽅⾯，std::shared_ptr没有提供
operator[]重载，所以数组索引操作需要借助怪异的指针算术。另⼀⽅⾯，std::shared_ptr⽀持转
换为指向基类的指针，这对于单个对象来说有效，但是当⽤于数组类型时相当于在类型系统上开洞。
（出于这个原因，std::unique_ptr禁⽌这种转换。）。更重要的是，C++11已经提供了很多内置数组
的候选⽅案（⽐如std::array , std::vector , std::string）。声明⼀个指向傻⽠数组的智能指针⼏
乎总是标识着糟糕的设计。
*/



