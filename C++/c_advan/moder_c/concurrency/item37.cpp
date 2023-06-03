#include<thread>
#include<chrono>
#include<future>
#include<iostream>
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
constexpr auto tenmilliom = 10000;
//return whether computation was performed; see Item2 for std::function
bool dowork(std::function<bool(int)> filter, int maxval = tenmilliom){
	std::vector<int> goodvals;
	ThreadRAII t(std::thread([&filter, maxval, &goodvals] {
		for (auto i = 0; i < maxval; i++) {
			if (filter(i))
				goodvals.push_back(i);
		}
	}),ThreadRAII::DtorAction::join);
	auto nh = t.get().native_handle();//
	//
	if (conditionAreStatisfied()) {
		t.get().join();
		//performComputation(goodvals);
		return true;
	}
	return false;

}
