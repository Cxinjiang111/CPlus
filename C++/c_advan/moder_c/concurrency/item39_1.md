将条件变量和flag的设计组合起来很常⽤。⼀个flag表⽰是否发⽣了感兴趣的事件，但是通过互斥锁同步 了对该flag的访问。因为互斥锁阻⽌并发该flag，所以如Item 40所述，不需要将flag设置为 std::atomic 。⼀个简单的bool类型就可以，检测任务代码如下：
std::condition_variable cv;
std::mutex m;
bool flag(false)// not a atomic
{   
    std::lock_guard<std::mutex> g(m); 
    flag=true;//tell the recting task(part 1)
}// unlock m 
cv.notify_one();

{
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk,[]{return flag;})//usr lambda to avoid spurious wakeup
}
这份代码解决了我们⼀直讨论的问题。⽆论是否反应线程在调⽤ wait 之前还是之后检测线程对条件变 量发出通知都可以⼯作，即使出现了虚假唤醒也可以⼯作，而且不需要轮询。但是仍然有些古怪，因为 检测任务通过奇怪的⽅式与反应线程通信。（译者注：下⾯的话挺绕的，可以参考原⽂）检测任务通知 条件变量告诉反应线程等待的事件可能发⽣了，反应线程必须通过检查flag来确保事件发⽣了。检测线 程设置flag来告诉反应线程事件确实发⽣了，但是检测线程⾸先需要通知条件变量唤醒反应线程来检查
flag。这种⽅案是可以⼯作的，但是不太优雅。
⼀个替代⽅案是让反应任务通过在检测任务设置的future上 wait 来避免使⽤条件变量，互斥锁和flag。 这可能听起来也是个古怪的⽅案。毕竟，Item 38中说明了future代表了从被调⽤⽅（通常是异步的）到 调⽤⽅的通信的接收端，这⾥的检测任务和反应任务没有调⽤-被调⽤的关系。然而，Item 38中也说说
明了通信新到发送端是 std::promise ，接收端是 future 不只能⽤在调⽤-被调⽤场景。这样的通信信 道可以被在任何你需要从程序⼀个地⽅传递到另⼀个地⽅的场景。这⾥，我们⽤来在检测任务和反应任 务之间传递信息，传递的信息就是感兴趣的事件是否已发⽣。
⽅案很简单。检测任务有⼀个 std::promise 对象（通信信道的写⼊），反应任务有对应的 std::future （通信信道的读取）。当反应任务看到事件已经发⽣，设置 std::promise 对象（写⼊到 通信信道）。同时，反应任务在 std::future 上等待。 wait 会锁住反应任务直到 std::promise 被设 置。
现在， std::promise和futures(std::future and std::shared_future) 都是需要参数类型的模 板。参数表明被传递的信息类型。在这⾥，没有数据被传递，只需要让反应任务知道 future 已经被设 置了。我们需要的类型是表明在 std::promise 和 futures 之间没有数据被传递。所以选择 void 。检 测任务使⽤ std::promise<void> ，反应任务使⽤ std::future<void> or std::shared_future<void> 。当感兴趣的事件发⽣时，检测任务设置 std::promise<void> ，反应任 务在 futures 上等待。即使反应任务不接收任何数据，通信信道可以让反应任务知道检测任务是否设置 了 void 数据（通过对 std::promise<void> 调⽤ set_value ）。
std::promise<void> p; // promise for communications channel
检测任务代码如下：
p.set_value(); // tell reacting task
反应任务代码如下：
 ...// prepare to react
 p.get_future().wait(); // wait on future corresponding to p 
 ... //react to event
 像使⽤flag的⽅法⼀样，此设计不需要互斥锁，⽆论检测任务是否在反应任务等待之前设置 std::promise 都可以⼯作，并且不受虚假唤醒的影响（只有条件变量才容易受到此影响）。与基于条 件变量的⽅法⼀样，反应任务真是被blocked，不会⼀直占⽤系统资源。是不是很完美？
当然不是，基于 future 的⽅法没有了上述问题，但是有其他新的问题。⽐如，Item 38中说明， std::promise 和 future 之间有共享状态，并且共享状态是动态分配的。因此你应该假定此设计会产⽣基于堆的分配和释放开销。

也许更重要的是， std::promise 只能设置⼀次。 std::promise 与 future 之间的通信是⼀次性的： 不能重复使⽤。这是与基于条件变量或者flag的明显差异，条件变量可以被重复通知，flag也可以重复清 除和设置。
⼀次通信可能没有你想象中那么⼤的限制。假定你想创建⼀个挂起的线程以避免想要使⽤⼀个线程执⾏ 程序的时候的线程创建的开销。或者你想在线程运⾏前对其进⾏设置，包括优先级和core affinity。C++并发API没有提供这种设置能⼒，但是提供了 native_handle() 获取原始线程的接口（通常获取的 是POXIC或者Windows的线程），这些低层次的API使你可以对线程设置优先级和 core affinity。