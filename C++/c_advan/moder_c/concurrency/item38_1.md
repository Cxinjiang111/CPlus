这些规则听起来好复杂。我们真正要处理的是⼀个简单的“正常”⾏为以及⼀个单独的例外。正常⾏为是 future 析构函数销毁 future 。那意味着不 join 也不 detach ，只销毁 future 的数据成员（当然，还 做了另⼀件事，就是对于多引⽤的共享状态引⽤计数减⼀。）
正常⾏为的例外情况仅在同时满⾜下列所有情况下才会执⾏：
关联 future 的共享状态是被调⽤了 std::async 创建的
任务的启动策略是 std::launch::async （参⻅Item 36），原因是运⾏时系统选择了该策略，或 者在对 std::async 的调⽤中指定了该策略。
future 是关联共享状态的最后⼀个引⽤。对于 std::future ，情况总是如此，对于 std::shared_future ，如果还有其他的 std::shared_future 引⽤相同的共享状态没有销毁， 就不是。
只有当上⾯的三个条件都满⾜时， future 的析构函数才会表现“异常”⾏为，就是在异步任务执⾏完之前block住。实际上，这相当于运⾏ std::async 创建的任务的线程隐式 join 。
通常会听到将这种异常的析构函数⾏为称为"Futures from std::async block in their destructors"。作 为近似描述没有问题，但是忽略了原因和细节，现在你已经知道了其中三味。

你可能想要了解更加深⼊。⽐如“为什么会有这样的规则”（译者注：这⾥的问题是意译，原⽂重复了问 题本⾝），这很合理。据我所知，标准委员会希望避免这个问题与隐式 detach （参⻅Item 37）相关 联，但是不想采取强制程序终⽌这种激进的⽅案（因此搞了 join ，同样参⻅Item 37），所以妥协使⽤ 隐式 join 。这个决定并⾮没有争议，并且认真讨论过在C++14中放弃这种⾏为。最后，决定先不改变， 所以C++11和C++14中这⾥的⾏为是⼀致的。
没有API来提供 future 是否指向 std::async 调⽤产⽣的共享状态，因此给定⼀个 std::future 对象， ⽆法判断是不是会在析构函数block等待异步任务的完成。这就产⽣了有意思的事情：
std::vector<std::future<void>> futs; // see Item 39 for info on std::future<void> 
class Widget // Widget objects might block in their dtors 
{
    public: ... 
private: 
    std::shared_future<double> fut;
 };
 当然，如果你有办法知道给定的 future 不满⾜上⾯条件的任意⼀条，你就可以确定析构函数不会执⾏ “异常”⾏为。⽐如，只有通过 std::async 创建的共享状态才有资格执⾏“异常”⾏为，但是有其他创建共 享状态的⽅式。⼀种是使⽤ std::packaged_task ，⼀个 std::packaged_task 对象准备⼀个函数（或 者其他可调⽤对象）来异步执⾏，然后将其结果放⼊共享状态中。然后通过 std::packaged_task 的 get_future 函数获取有关该共享状态的信息：
int calcValue(); // func to run 
std::packaged_task<int()> pt(calcValue); // wrap calcValue so it can run asynchrously 
auto fut = pt.get_future(); // get future for pt
此时，我们知道 future 没有关联 std::async 创建的共享状态，所以析构函数肯定正常⽅式执⾏。

⼀旦被创建， std::packaged_task 类型的pt可能会在线程上执⾏。（译者注：后⾯有些啰嗦的话这⾥ 不完整翻译。。⼤意就是可以再次使⽤ std::async 来执⾏，但是那就不⽤ std::packaged_task 了）
std::packaged_task 不能拷⻉，所以当 pt 被传递给 std::thread 时是右值传递（通过move，参⻅Item 23）
std::thread t(std::move(pt)); // run pt on 
这个例⼦是你对于 future 的析构函数的正常⾏为有⼀些了解，但是将这些语句放在⼀个作⽤域的语句 块⾥更容易：
{ // begin block 
    std::packaged_task<int()> pt(calcValue); 
    auto fut = pt.get_future(); 
    std::thread t(std::move(pt)); ...
 } // end block
此处最有趣的代码是在创建 std::thread 对象t之后的"..."。"..."有三种可能性：
对t不做什么。这种情况，t会在语句块结束joinable，这会使得程序终⽌（参⻅Item 37）
对t调⽤ join 。这种情况，不需要fut的析构函数block，因为 join 被显式调⽤了
对t调⽤ detach 。这种情况，不需要在fut的析构函数执⾏ detach ，因为显式调⽤了 换句话说，当你有⼀个关联了 std::packaged_task 创建的共享状态的 future 时，不需要采取特殊的 销毁策略，通常你会代码中做这些。
需要记住的事
future 的正常析构⾏为就是销毁 future 本⾝的成员数据 
最后⼀个引⽤ std::async 创建共享状态的 future 析构函数会在任务结束前block