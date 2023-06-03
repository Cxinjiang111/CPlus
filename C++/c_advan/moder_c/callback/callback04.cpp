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
    auto bindFun=std::bind(&testFun,std::placeholders::_1,3);
    int ret=bindFun(5,2);
	std::cout << "普通函数_1：" << ret << std::endl;
    auto bindFun2=std::bind(lambdaExps,std::placeholders::_1,std::placeholders::_2);
    ret=bindFun2(6,2);
    	std::cout << "Lambda表达式：" << ret << std::endl;
    Functor testFunctor;
    auto bindFun3=std::bind(testFunctor,7,std::placeholders::_2);
    ret=bindFun3(5,7);
	std::cout << "仿函数：" << ret << std::endl;
    TestClass testObj;
    auto bindFun5=std::bind(&TestClass::classMemeberFun,testObj,std::placeholders::_1,8);
    ret=bindFun5(10,5);
	std::cout << "类成员函数：" << ret << std::endl;
    auto bindFun6=std::bind(&TestClass::staticMemberFun,std::placeholders::_1,std::placeholders::_2);
    ret=bindFun6(10,20);
std::cout << "类静态成员函数：" << ret << std::endl;




}
