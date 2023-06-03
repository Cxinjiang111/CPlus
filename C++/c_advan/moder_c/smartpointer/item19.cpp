#include <iostream>
#include <memory>
#include <stdlib.h>
//Item 19:对于共享资源使⽤std::shared_ptr
/*

*/
class Widget{
    
};
//自定义销毁器
auto logginDel=[](Widget *pw){
    makeLogEntry(pw);
    delete pw;
};
std::unique_ptr<Widget,decltype(logginDel)>upw(new Widget,logginDel);
std::shared_ptr<Widget>;
spw(new Widget,loggingDel);
auto customDeleter1 = [](Widget *pw) { … };//自定义销毁器
auto customDeleter2 = [](Widget *pw) { … };
std::shared_ptr<Widget> pw1(new Widget, customDeleter1);
std::shared_ptr<Widget> pw2(new Widget, customDeleter2);
std::vector<std::shared_ptr<Widget>> vpw{ pw1, pw2 };
/*
它们也能相互赋值，也可以传⼊形参为std::shared_ptr<Widget>的函数。但是std::unique_ptr就
不⾏，因为std::unique_ptr把销毁器视作类型的⼀部分。  unique_ptr：具有唯一性 
另⼀个不同于std::unique_ptr的地⽅是，指定⾃定义销毁器不会改变std::shared_ptr对象的⼤
小。不管销毁器是什么，⼀个std::shared_ptr对象都是两个指针⼤小。这是个好消息，但是它应该让
你隐隐约约不安。⾃定义销毁器可以是函数对象，函数对象可以包含任意多的数据。它意味着函数对象
是任意⼤的。std::shared_ptr怎么能引⽤⼀个任意⼤的销毁器而不使⽤更多的内存？
它不能。它必须使⽤更多的内存。然而，那部分内存不是std::shared_ptr对象的⼀部分。那部分在堆
上⾯，只要std::shared_ptr⾃定义了分配器，那部分内存随便在哪都⾏。我前⾯提到了
std::shared_ptr对象包含了所指对象的引⽤计数。没错，但是有点误导⼈。因为引⽤计数是另⼀个更
⼤的数据结构的⼀部分，那个数据结构通常叫做控制块（control block）。控制块包含除了引⽤计数值
外的⼀个⾃定义销毁器的拷⻉，当然前提是存在⾃定义销毁器。如果⽤⼾还指定了⾃定义分配器，控制
器也会包含⼀个分配器的拷⻉。控制块可能还包含⼀些额外的数据，正如Item21提到的，⼀个次级引⽤
计数weak count，但是⽬前我们先忽略它。我们可以想象std::shared_ptr对象在内存中是这样：

当std::shared_ptr对象⼀创建，对象控制块就建⽴了。⾄少我们期望是如此。通常，对于⼀个创建指
向对象的std::shared_ptr的函数来说不可能知道是否有其他std::shared_ptr早已指向那个对象，
所以控制块的创建会遵循下⾯⼏条规则：
std::make_shared总是创建⼀个控制块(参⻅Item21)。它创建⼀个指向新对象的指针，所以可以
肯定std::make_shared调⽤时对象不存在其他控制块。
当从独占指针上构造出std::shared_ptr时会创建控制块（即std::unique_ptr或者
std::auto_ptr）。独占指针没有使⽤控制块，所以指针指向的对象没有关联其他控制块。（作
为构造的⼀部分，std::shared_ptr侵占独占指针所指向的对象的独占权，所以std::unique_ptr被设置为null）

当从原始指针上构造出std::shared_ptr时会创建控制块。如果你想从⼀个早已存在控制块的对
象上创建std::shared_ptr，你将假定传递⼀个std::shared_ptr或者std::weak_ptr作为构
造函数实参，而不是原始指针。⽤std::shared_ptr或者std::weak_ptr作为构造函数实参创
建std::shared_ptr不会创建新控制块，因为它可以依赖传递来的智能指针指向控制块。


*/
/*
这些规则造成的后果就是从原始指针上构造超过⼀个std::shared_ptr就会让你走上未定义⾏为的快⻋
道，因为指向的对象有多个控制块关联。多个控制块意味着多个引⽤计数值，多个引⽤计数值意味着对
象将会被销毁多次（每个引⽤计数⼀次）。那意味着下⾯的代码是有问题的，很有问题，问题很⼤：
*/
//感觉这种情况特别容易写出来，而且还没有意识
auto pw = new Widget; // pw是原始指针
std::shared_ptr<Widget> spw1(pw, loggingDel); // 为*pw创建控制块
std::shared_ptr<Widget> spw2(pw, loggingDel); // 为*pw创建第⼆个控制块
//这个就会被销毁两次
/*
创建原始指针指向动态分配的对象很糟糕，因为它完全背离了这章的建议：对于共享资源使⽤
std::shared_ptr而不是原始指针。（如果你忘记了该建议的动机，请翻到115⻚）。撇开那个不说，
创建pw那⼀⾏代码虽然让⼈厌恶，但是⾄少不会造成未定义程序⾏为。
现在，传给spw1的构造函数⼀个原始指针，它会为指向的对象创建⼀个控制块（引⽤计数值在⾥⾯）。
这种情况下，指向的对象是*pw。就其本⾝而⾔没什么问题，但是将同样的原始指针传递给spw2的构
造函数会再次为*pw创建⼀个控制块。因此*pw有两个引⽤计数值，每⼀个最后都会变成零，然后最终
导致*pw销毁两次。第⼆个销毁会产⽣未定义⾏为。
std::shared_ptr给我们上了两堂课。第⼀，避免传给std::shared_ptr构造函数原始指针。通常替
代⽅案是使⽤std::make_shared (参⻅Item21)，不过上⾯例⼦中，我们使⽤了⾃定义销毁器，⽤
std::make_shared就没办法做到。第⼆，如果你必须传给std::shared_ptr构造函数原始指针，直
接传new出来的结果，不要传指针变量。如果上⾯代码第⼀部分这样重写：
*/

std::shared_ptr<Widget> spw1(new Widget,loggingDel); // 直接使⽤new的结果
//会少了很多创建第⼆个从原始指针上构造std::shared_ptr的诱惑。相应的，创建spw2也会很⾃然的
//⽤spw1作为初始化参数（即⽤std::shared_ptr拷⻉构造），那就没什么问题了：
std::shared_ptr<Widget> spw2(spw1); // spw2使⽤spw1⼀样的控制块
/*
⼀个尤其令⼈意外的地⽅是使⽤this原始指针作为std::shared_ptr构造函数实参的时候可能导致创建
多个控制块。假设我们的程序使⽤std::shared_ptr管理Widget对象，我们有⼀个数据结构⽤于跟踪
已经处理过的Widget对象：
*/