Item36： 确保在异步为必须时，才指定 std::launch::async

当你调⽤ std::async 执⾏函数时（或者其他可调⽤对象），你通常希望异步执⾏函数。但是这并不⼀
定是你想要 std::async 执⾏的操作。你确实通过 std::async launch policy（译者注：这⾥没有翻 译）要求执⾏函数，有两种标准policy，都通过 std::launch 域的枚举类型表⽰（参⻅Item10关于枚举 的更多细节）。假定⼀个函数f传给 std::async 来执⾏：
std::launch::async 的launch policy意味着f必须异步执⾏，即在不同的线程
std::launch::deferred 的launch policy意味着f仅仅在当调⽤ get或者wait要求std::async的返回值时才执⾏。这表⽰f推迟到被求值才延迟执⾏（译者注：异步与并发是两个不同概念，这⾥侧重于惰性求值）。当get或wait被调⽤，f会同步执⾏，即调⽤⽅停⽌直到f运⾏结束。如果 get和wait 都没有被调⽤，f将不会被执⾏

auto fut1=std::async(f);
auto fut2=std::async(std::launch::async|std::launch::deferred,f);
因此默认策略允许f异步或者同步执⾏。如同Item 35中指出，这种灵活性允许std::async和标准库的 线程管理组件（负责线程的创建或销毁）避免超载。这就是使⽤ std::async 并发编程如此⽅便的原因。

但是，使⽤默认启动策略的 std::async 也有⼀些有趣的影响。给定⼀个线程t执⾏此语句：
auto fut = std::async(f); // run f using default launch policy
⽆法预测f是否会与fut同时运⾏，因为f可能被安排延迟运⾏
⽆法预测f是否会在调⽤ get或wait 的线程上执⾏。如果那个线程是t，含义就是⽆法预测f是否也在 线程t上执⾏
⽆法预测f是否执⾏，因为不能确保 get或者wait 会被调⽤

默认启动策略的调度灵活性导致使⽤线程本地变量⽐较⿇烦，因为这意味着如果f读写了线程本地存储 （thread-local storage, TLS），不可能预测到哪个线程的本地变量被访问
auto fut = std::async(f); // TLS for f possibly for independent thread, but possibly for thread invoking get or wait on fut
还会影响到基于超时机制的wait循环，因为在task的 wait_for 或者 wait_until 调⽤中（参⻅Item35）会产⽣延迟求值（ std::launch::deferred ）。





