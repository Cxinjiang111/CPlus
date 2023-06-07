#include<iostream>
#include<thread>
#include<mutex>
class A
{
public:
	A();
	~A();


private:
	int m_num;
};
A::A()
{
    //A这个构造函数非常耗时
	int ss = 0;
	for (int i = 0; i < 10000; ++i)
	{
		ss+=i;
	}
	std::cout << "A create finished" <<ss<< std::endl;
}
A::~A()
{

}

std::mutex m;
 A *pa = nullptr;
int sum = 0;
void create()
{
	for (int i = 0; i < 50; i++)
	{
		sum += i;
	}
	if (pa == nullptr)
	{
		m.lock();
		if (pa == nullptr)
			for (int i = 0; i < 5000; ++i)
			{
				sum += i;
			}
			std::cout << "crate ===" << std::endl;
			pa = new A();
		m.unlock();
	}
	if (pa != nullptr)
	{
		std::cout << "crate" << std::endl;
	}
}
void create2()
{
	for (int i = 0; i < 47; i++)
	{
		sum += i;
	}
	if (pa == nullptr)
	{
		m.lock();
		if (pa == nullptr)
			for (int i = 0; i < 5000; ++i)
			{
				sum += i;
			}
		std::cout << "crate2 ====" << std::endl;
			pa = new A();
		m.unlock();
	}
	if (pa != nullptr)
	{
		std::cout << "crate2" << std::endl;
	}
}
void create3()
{
	for (int i = 0; i < 49; i++)
	{
		sum += i;
	}
	if (pa == nullptr)
	{
		m.lock();
		if (pa == nullptr)
			for (int i = 0; i < 5000; ++i)
			{
				sum += i;
			}
		std::cout << "crate3 ===" << std::endl;
			pa = new A();
		m.unlock();
	}
	if (pa != nullptr)
	{
		std::cout << "crate3" << std::endl;
	}
}
void create4()
{
	for (int i = 0; i < 54; i++)
	{
		sum += i;
	}
	if (pa == nullptr)
	{
		m.lock();
		if (pa == nullptr)
        //存在barries
			for (int i = 0; i < 5000; ++i)
			{
				sum += i;
			}
			std::cout << "crate4 ===" << std::endl;
			pa = new A();
		m.unlock();
	}
	if (pa != nullptr)
	{
		std::cout << "crate4" << std::endl;
	}
}
int main()
{
	int msum = 0;
	for (int i = 0; i < 5000; i++)
	{
		msum += i;
	}
	std::thread t1(create);
	std::thread t2(create2);
	std::thread t3(create3);
	std::thread t4(create4);

	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
		
	while (1) {

	}
	std::cout << msum << std::endl;
	return 0;
}

/*
构造函数创建多次
crate3 ===
A create finished704982704
crate3
crate ===
A create finished704982704
cratecrate2 ====

A create finished704982704
crate2
crate4 ===
A create finished704982704
crate4
*/