#include<iostream>
#include<functional>
#include<future>
#include<thread>
std::promise<int> prom;//返回值为 std::future<int>
void print_global_promise(){
    std::future<int> fut=prom.get_future();
    int x=fut.get();
    std::cout<<x<<"\n";
}
int main(){
    std::thread t1(print_global_promise);
    prom.set_value(10);
    t1.join();

    prom=std::promise<int>(); // prom 被move赋值为一个新的 promise 对象.
    std::thread t2(print_global_promise);
    prom.set_value(20);
    //t1.join();//error 应为prom已经转移  
    t2.join();

    return 0;
}



