#include <iostream>     // std::cout
#include <utility>      // std::move
#include <future>       // std::packaged_task, std::future
#include <thread>       // std::thread
/*
与std::promise 类似， std::packaged_task 也禁用了普通的赋值操作运算，只允许 move 赋值运算。
std::packaged_task::valid 介绍
检查当前 packaged_task 是否和一个有效的共享状态相关联，对于由默认构造函数生成的packaged_task对象，
该函数返回 false，除非中间进行了 move 赋值操作或者 swap 操作。
*/
// 在新线程中启动一个 int(int) packaged_task.
std::future<int> launcher(std::packaged_task<int(int)>& tsk, int arg)
{
    if (tsk.valid()) {
        std::future<int> ret = tsk.get_future();
        std::thread (std::move(tsk),arg).detach();
        return ret;
    }
    else return std::future<int>();
}

int main ()
{
    std::packaged_task<int(int)> tsk([](int x){return x*2;});

    std::future<int> fut = launcher(tsk,25);

    std::cout << "The double of 25 is " << fut.get() << ".\n";

    return 0;
}