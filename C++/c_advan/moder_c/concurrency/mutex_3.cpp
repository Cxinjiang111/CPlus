#include<iostream>
#include<functional>
#include<future>
#include<exception>
#include<thread>
/*
std::promise::get_future 介绍
该函数返回一个与 promise 共享状态相关联的 future 。返回的 future 对象可以访问由promise对象设置在共享状态上的值或者某个异常对象。
只能从 promise 共享状态获取一个 future 对象。在调用该函数之后，promise 对象通常会在某个时间点准备好(设置一个值或者一个异常对象)，
如果不设置值或者异常，promise 对象在析构时会自动地设置一个 future_error 异常(broken_promise)来设置其自身的准备状态。
上面的例子中已经提到了 get_future，此处不再重复。
std::promise::set_value 介绍
generic template (1)	
                        void set_value (const T& val);
                        void set_value (T&& val);
specializations (2)	特化
                        void promise<R&>::set_value (R& val);   // when T is a reference type (R&)
                        void promise<void>::set_value (void);   // when T is void
设置共享状态的值，此后 promise 的共享状态标志变为 ready.
std::promise::set_exception 介绍
为 promise 设置异常，此后 promise 的共享状态变标志变为 ready，
例子如下，线程1从终端接收一个整数，线程2将该整数打印出来，如果线程1接收一个非整数，则为 promise 设置一个异常(failbit) ，
线程2 在std::future::get 是抛出该异常。
*/
void get_int(std::promise<int>&prom){
    int x;
    std::cout<<"enter an interger value";
    std::cin.exceptions(std::ios::failbit);//std::ios::failbit promise 设置一个异常(failbit) 
    try{
        std::cin>>x;
        prom.set_value(x);
    }
    catch(std::exception){
        prom.set_exception(std::current_exception());
    }
}
void print_int(std::future<int> &fut){
    try{
        int x=fut.get();
        std::cout<<"value"<<x<<"\n";

    }catch(std::exception &e){
        //那我怎么才能使他抛出异常
        std::cout<<"expection caught"<<e.what()<<"\n";//线程2 在std::future::get 是抛出该异常
    }

}
/*
std::promise::set_value_at_thread_exit 介绍
设置共享状态的值，但是不将共享状态的标志设置为 ready，当线程退出时该 promise 对象会自动设置为ready。
如果某个std::future对象与该promise对象的共享状态相关联，并且该 future 正在调用 get，则调用get的线程会被阻塞，
当线程退出时，调用future::get的线程解除阻塞，同时get返回set_value_at_thread_exit 所设置的值。
注意，该函数已经设置了promise共享状态的值，如果在线程结束之前有其他设置或者修改共享状态的值的操作，
则会抛出 future_error(promise_already_satisfied)。

std::promise::swap 介绍
交换 promise 的共享状态。

*/
int main(){
    std::promise<int> prom;
    std::future<int>fut=prom.get_future();
    std::thread t1(get_int,std::ref(prom));
    std::thread t2(print_int,std::ref(fut));

    t1.join();
    t2.join();
    return 0;
}