#include<thread>
#include<chrono>
#include<future>
#include<iostream>
std::promise<void> p;
void react();
void detect(){// create thread

    std::thread t([]{
        p.get_future().wait(); // suspend t until future is set
        react();
        // here, t is suspended prior to call to react
    });
    p.set_value();// unsuspend t (and thus call react)
    t.join(); // make t unjoinable(see Item 37)
}
class ThreadRAII {
public:
	enum class DtorAction { join, detach };//执行的两个动作
	ThreadRAII(std::thread&& t, DtorAction a) :action(a), t(std::move(t)) {}
	~ThreadRAII() { //析构函数被隐式调用，join 或者detach被隐式调用
		if (t.joinable()) {
			if (action == DtorAction::join) {
				t.join();
			}
			else {
				t.detach();
			}
		}
	}
	std::thread& get() { return t; }
	ThreadRAII& operator=(ThreadRAII&&) = default;
	ThreadRAII(ThreadRAII&&) = default;
private:
	DtorAction action;
	std::thread t;

};
//采用RAII包装一下
void detect(){// create thread
    ThreadRAII t(std::thread ([]{
        p.get_future().wait(); // suspend t until future is set
        react();
        // here, t is suspended prior to call to react
    }),ThreadRAII::DtorAction::join);
    p.set_value();// unsuspend t (and thus call react)

}
/*
这样看起来安全多了。问题在于第⼀个"..."区域（注释了thread inside tr is suspended here），
如果异常发⽣， p.set_value() 永远不会调⽤，这意味着lambda中的wait永远不会返回，即lambda不会结束，
问题就是，因为RAII对象tr再析构函数中join。换句话说，如果在第⼀个"..."中发⽣了异常，函数挂 起，因为tr的析构不会被调⽤。
*/
