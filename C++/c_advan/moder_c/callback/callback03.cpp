#include<iostream>
#include<vector>
#include<functional>
using namespace std;
int testFun(int a,int b)
{
    return a+b;
}
auto lambdaExps=[](int a,int b)
{
    return a+b;
};
// 仿函数
class Functor {
public:
	int operator()(int a, int b) {
		return a + b;
	}
};
class TestClass{
    public:
    int classMemeberFun(int a,int b){
        return a+b;
    }
    static int staticMemberFun(int a,int b){
        return a+b;
    }
};
int main()
{
    //普通函数
    std::function<int(int ,int )> functional1=testFun;
    int ret=functional1(10,10);
    std::cout << "普通函数：" << ret << std::endl;
    // 普通函数指针
    functional1=&testFun;//去函数指针
    ret=functional1(10,10);
    std::cout << "普通函数指针：" << ret << std::endl;
    //Lambda表达式
    functional1=lambdaExps;
    ret=functional1(10,10);
    std::cout << "Lambda表达式：" << ret << std::endl;
    // 仿函数
    functional1=Functor();
    ret=functional1(10,10);
	std::cout << "仿函数：" << ret << std::endl;
    //
    TestClass testObj;
    functional1=std::bind(&TestClass::classMemeberFun,testObj,
    std::placeholders::_1,std::placeholders::_2);
    ret=functional1(10,20);
    std::cout << "类成员函数：" << ret << std::endl;
    functional1=TestClass::staticMemberFun;
    functional1(10,20);
	std::cout << "类静态成员函数：" << ret << std::endl;
}
