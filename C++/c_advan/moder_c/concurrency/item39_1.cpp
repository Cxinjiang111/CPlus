#include<thread>
#include<chrono>
#include<future>
#include<vector>
#include<iostream>
int threadsToRun=10;
std::promise<void> p;
void react();
void detect(){// create thread
    auto sf=p.get_future().share();// sf's type is std::shared_future<void>
    std::vector<std::thread> vt; // container for reacting threads
    for(int i=0;i<threadsToRun;i++){
        vt.emplace_back([sf]{
            sf.wait();
            react();
        }); // wait on local copy of sf; see Item 43 for info on emplace_back
    }
    p.set_value();
    for(auto &t:vt){
        t.join();// make all threads unjoinable: see Item2 for info on "auto&"
    }
}
/*
需要记住的事 
对于简单的事件通信，条件变量需要⼀个多余的互斥锁，对检测和反应任务的相对进度有约束，并且需要反应任务来验证事件是否已发⽣ 
基于flag的设计避免的上⼀条的问题，但是不是真正的挂起反应任务 组合条件变量和flag使⽤，上⾯的问题都解决了，
但是逻辑不让⼈愉快 使⽤ std::promise和future 的⽅案，要考虑堆内存的分配和销毁开销，同时有只能使⽤⼀次通信 的限制
*/
