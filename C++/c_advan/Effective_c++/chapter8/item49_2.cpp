#include<iostream>
using namespace std;
class A{
public:
    static int num1;
};
int A::num1=5;//没有就会报错 相当于一个全局变量 
//他不不需要显式声明一个类对象，通过类对象去调用此变量或成员函数，形成一个全局变量
//会在全局进行修改
//无须创建任何对象实例就可以访问，而静态成员函数可不建立对象就可以被使用
//或者说静态函数与一般函数没有太大的区别，只是访问有限制，静态变量跟一般的全局变量的区别就是访问有限制。
void fun(A &a)
{
    std::cout<<"fun before"<<A::num1<<std::endl;
    a.num1=10;
    A::num1=50;
    std::cout<<"fun later"<<a.num1<<endl;
}
int main()
{
    std::cout<<A::num1<<std::endl;
    A a;
    a.num1=4;
    fun(a);

    std::cout<<A::num1<<endl;
}

