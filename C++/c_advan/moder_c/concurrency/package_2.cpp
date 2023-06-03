#include<iostream>
#include<functional>
#include<future>
#include<exception>
#include<thread>
/*
std::packaged_task 构造函数
default (1)	            packaged_task() noexcept;
initialization (2)	    template <class Fn>
                        explicit packaged_task (Fn&& fn);
with allocator (3)	    template <class Fn, class Alloc>
                        explicit packaged_task (allocator_arg_t aa, const Alloc& alloc, Fn&& fn);
copy [deleted] (4)	    packaged_task (const packaged_task&) = delete;
move (5)	            packaged_task (packaged_task&& x) noexcept;
std::packaged_task 构造函数共有 5 中形式，不过拷贝构造已经被禁用了。下面简单地介绍一下上述几种构造函数的语义：

1 默认构造函数，初始化一个空的共享状态，并且该 packaged_task 对象无包装任务。
2 初始化一个共享状态，并且被包装任务由参数 fn 指定。
3 带自定义内存分配器的构造函数，与默认构造函数类似，但是使用自定义分配器来分配共享状态。
4 拷贝构造函数，被禁用。
5 移动构造函数。

*/
#include <iostream>     // std::cout
#include <utility>      // std::move
#include <future>       // std::packaged_task, std::future
#include <thread>       // std::thread

int main ()
{
    std::packaged_task<int(int)> foo; // 默认构造函数.

    // 使用 lambda 表达式初始化一个 packaged_task 对象.
    std::packaged_task<int(int)> bar([](int x){return x*2;});

    foo = std::move(bar); // move-赋值操作，也是 C++11 中的新特性.

    // 获取与 packaged_task 共享状态相关联的 future 对象.
    std::future<int> ret = foo.get_future();

    std::thread(std::move(foo), 10).detach(); // 产生线程，调用被包装的任务.

    int value = ret.get(); // 等待任务完成并获取结果.
    std::cout << "The double of 10 is " << value << ".\n";

return 0;
}