#include<thread>
/*
如果开发者想要异步执⾏ doAsyncWork 函数，通常有两种⽅式。其⼀是通过创建 std::thread 执⾏ doAsyncWork ， ⽐如
*/
int dowork();
std::thread t1(dowork);
//其⼆是将doAsyncWork传递给std::async，⼀种基于任务的策略：
auto f1=std::async(dowork);