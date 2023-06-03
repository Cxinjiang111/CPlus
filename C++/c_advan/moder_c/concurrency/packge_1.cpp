#include<iostream>
#include<functional>
#include<future>
#include<exception>
#include<thread>
/*
std::packaged_task 包装一个可调用的对象，并且允许异步获取该可调用对象产生的结果，从包装可调用对象意义上来讲，
std::packaged_task与std::function 类似，只不过 std::packaged_task 将其包装的可调用对象的执行结果传递给一个std::future对象
（该对象通常在另外一个线程中获取 std::packaged_task 任务的执行结果）。
std::packaged_task 对象内部包含了两个最基本元素，
一、被包装的任务(stored task)，任务(task)是一个可调用的对象，如函数指针、成员函数指针或者函数对象，             可传参
二、共享状态(shared state)，用于保存任务的返回值，可以通过 std::future 对象来达到异步访问共享状态的效果。       存在返回值 并使其有返回值 值可共享
可以通过 std::packged_task::get_future 来获取与共享状态相关联的 std::future 对象。在调用该函数之后，两个对象共享相同的共享状态，具体解释如下：
std::packaged_task 对象是异步 Provider，它在某一时刻通过调用被包装的任务来设置共享状态的值。
std::future 对象是一个异步返回对象，通过它可以获得共享状态的值，当然在必要的时候需要等待共享状态标志变为 ready.
*/
int countdown(int from,int to){
    for(int i=from;i<to;++i){
        std::cout<<i<<"\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout<<"finished \n";
    return from-to;
}
int main(){
    std::packaged_task<int(int,int)> task(countdown);//将任务打包 包的第一个特性 传函数
    std::future<int> ret=task.get_future(); //   包的第2个特性 提供共享状态的返回值
    // 
    std::thread th(std::move(task),10,0);//执行包任务
    int value=ret.get(); //获取线程返回值
    std::cout<<"value:"<<value<<"\n";
    th.join();
    return 0;
}
