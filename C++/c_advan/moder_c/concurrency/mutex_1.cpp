#include<iostream>
#include<functional>
#include<future>
#include<thread>
/*
promise 对象可以保存某一类型 T 的值，该值可被 future 对象读取（可能在另外一个线程中），
因此 promise 也提供了一种线程同步的手段。在 promise 对象构造时可以和一个共享状态（通常是std::future）相关联，
并可以在相关联的共享状态(std::future)上保存一个类型为 T 的值。
可以通过 get_future 来获取与该 promise 对象相关联的 future 对象，调用该函数之后，两个对象共享相同的共享状态(shared state)

promise 对象是异步 Provider，它可以在某一时刻设置共享状态的值。
future 对象可以异步返回共享状态的值，或者在必要的情况下阻塞调用者并等待共享状态标志变为ready，然后才能获取共享状态的值。
std::promise 构造函数
default (1)	                    promise();
with allocator (2)	 template <class Alloc> promise (allocator_arg_t aa, const Alloc& alloc);
copy [deleted] (3)	        promise (const promise&) = delete;
move (4)	                promise (promise&& x) noexcept;
默认构造函数，初始化一个空的共享状态。
带自定义内存分配器的构造函数，与默认构造函数类似，但是使用自定义分配器来分配共享状态。
拷贝构造函数，被禁用。
移动构造函数。
*/
void print_int(std::future<int>&fut){
    int x=fut.get();// 获取共享状态的值.
    std::cout<<x<<"\n";
}
int main(){
    std::promise<int> prom ;// 生成一个 std::promise<int> 对象. 可提供一种线程同步
    std::future<int> fut=prom.get_future();//和 future 关联. 共享状态

    std::thread t1(print_int,std::ref(fut));// 将 future 交给另外一个线程t.
    prom.set_value(10);// 设置共享状态的值, 此处和线程t保持同步. 这样设置共享状态值，由于prom能保证线程同步
    //所以能保证set——value的值线程能得到
    t1.join();
    return 0;
}