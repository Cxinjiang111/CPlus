Item 38：关注不同线程句柄的析构⾏为
Item 37中说明了joinable的 std::thread 对应于可执⾏的系统线程。non-defered任务的 future （参 ⻅Item 36）与系统线程有相似的关系。因此，可以将 std::thread 对象和 future 对象都视作系统线 程的句柄。

从这个⻆度来说，有趣的是 std::thread 和 futures 在析构时有相当不同的⾏为。在Item 37中说明，
joinable的 std::thread 析构会终⽌你的程序，因为两个其他的替代选择--隐式 join 或者隐式 detach 都是更加糟糕的。但是， futures 的析构表现有时就像执⾏了隐式 join， 有时⼜是隐式执⾏了 detach ，有时⼜没有执⾏这两个选择。永远不会造成程序终⽌。这个线程句柄多种表现值得研究⼀ 下。

我们可以观察到实际上 future 是通信信道的⼀端（被调⽤者通过该信道将结果发送给调⽤者）。被调 ⽤者（通常是异步执⾏）将计算结果写⼊通信信道中（通过 std::promise 对象），调⽤者使⽤ future 读取结果。你可以想象成下⾯的图⽰，虚线表⽰信息的流动⽅向：

caller(future)<-----------------------callee(std::promise)
但是被调⽤者的结果存储在哪⾥？被调⽤者会在调⽤者 get 相关的 future 之前执⾏完成，所以结果不 能存储在被调⽤者的 std::promise 。这个对象是局部的，当被调⽤者执⾏结束后，会被销毁。

结果同样不能存储在调⽤者的 future ，因为 std::future 可能会被⽤来创建 std::shared_future (这会将被调⽤者的结果所有权从 std::future 转移给 std::shared_future )， 而 std::shared_future 在 std::future 被销毁之后被复制很多次。鉴于不是所有的结果都可以被拷 ⻉（有些只能移动）和结果的声明周期与最后⼀个引⽤它的 future ⼀样⻓，哪个才是被调⽤者⽤来存 储结果的？这两个问题。

因为与被调⽤者关联的对象和调⽤者关联的对象都不适合存储这个结果，必须存储在两者之外的位置。 此位置称为共享状态（shared state）。共享状态通常是基于堆的对象，但是标准并未指定其类型、接口 和实现。标准库的作者可以通过任何他们喜欢的⽅式来实现共享状态。

caller(future)<------------calle's result(share state)-----------callee(std::promise)
共享状态的存在⾮常重要，因为 future 的析构⾏为--这个Item的话题---取决于关联 future 的共享状 态。
Non-defered任务（启动参数为 std::launch::async ）的最后⼀个关联共享状态的 future 析构 函数会在任务完成之前block住。本质上，这种 future 的析构对执⾏异步任务的线程做了隐式的 join 。
future 其他对象的析构简单的销毁。对于异步执⾏的任务，就像对底层的线程执⾏ detach 。对 于defered任务的最后⼀种 future ，意味着这个defered任务永远不会执⾏了。


