#include<thread>
#include<chrono>
#include<future>
#include<iostream>
using namespace std;
using namespace std::literals;
void f() 
{
	std::this_thread::sleep_for(1s);
}
void t1() {
	auto fut1 = std::async(f);
	//会循环等待  但是如果f是延迟执⾏， fut.wait_for 将总是返回 std::future_status::deferred
	while (fut1.wait_for(100ms) != std::future_status::ready)

	{
		std::cout << "hello" << std::endl;
	}
	/*
	hello
	hello
	hello
	hello
	hello
	hello
	hello
	hello
	hello
	*/
/*
如果f与调⽤ std::async 的线程同时运⾏（即，如果为f选择的启动策略是 std::launch::async ）， 
这⾥没有问题（假定f最终执⾏完毕），但是如果f是延迟执⾏，fut.wait_for将总是返回std::future_status::deferred 。
这表⽰循环会永远执⾏下去。
这种错误很容易在开发和单元测试中忽略，因为它可能在负载过⾼时才能显现出来。
当机器负载过重 时，任务推迟执⾏才最有可能发⽣。毕竟，如果硬件没有超载，没有理由不安排任务并发执⾏。


*/

}
int main() {
	auto fut = std::async(f);
    //我看是否存在推迟执行函数
    //只需要检查与 std::async 的future是否被延迟执⾏即可，你不想等待任何事，只想查看返回值是否
	if (fut.wait_for(0s) == std::future_status::deferred) {
		cout << "任务 没有被延迟" << endl;
	}
	else {
		while (fut.wait_for(100ms)!=std::future_status::ready)
		{
			cout << "hello " << endl;
		}
	}
	//fut.wait();
    /*
修复也是很简单的：只需要检查与 std::async 的future是否被延迟执⾏即可，那样就会避免进⼊⽆限 循环。
不幸的是，没有直接的⽅法来查看future是否被延迟执⾏。相反，你必须调⽤⼀个超时函数----⽐如 wait_for 这种函数。
在这个逻辑中，你不想等待任何事，只想查看返回值是否std::future_status::deferred，如果是就使⽤0调⽤ wait_for 来终⽌循环。   
这些各种考虑的结果就是，只要满⾜以下条件， std::async 的默认启动策略就可以使⽤：
task不需要和执⾏ get or wait 的线程并⾏执⾏
不会读写线程的线程本地变量
可以保证在 std::async 返回的将来会调⽤ get or wait ，或者该任务可能永远不会执⾏是可以接 受的
使⽤ wait_for or wait_until 编码时考虑deferred状态
如果上述条件任何⼀个都满⾜不了，你可能想要保证 std::async 的任务真正的异步执⾏。
进⾏此操作 的⽅法是调⽤时，将 std::launch::async 作为第⼀个参数传递：
auto fut = std::async(std::launch::async, f); // launch f asynchronously
    */
	cout << "end";
	return 0;
}