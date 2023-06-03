/*
std::packaged_task::get_future 介绍

返回一个与 packaged_task 对象共享状态相关的 future 对象。
返回的future 对象可以获得由另外一个线程在该packaged_task 对象的共享状态上设置的某个值或者异常。
*/
#include <iostream>     // std::cout
#include <utility>      // std::move
#include <future>       // std::packaged_task, std::future
#include <thread>       // std::thread

int main ()
{
    std::packaged_task<int(int)> tsk([](int x) { return x * 3; }); // package task

    std::future<int> fut = tsk.get_future();   // 获取 future 对象.

    std::thread(std::move(tsk), 100).detach();   // 生成新线程并调用packaged_task.

    int value = fut.get();                     // 等待任务完成, 并获取结果.

    std::cout << "The triple of 100 is " << value << ".\n";

    return 0;
}