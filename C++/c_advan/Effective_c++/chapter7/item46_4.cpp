#include<iostream>
using namespace std;
class A{
public:
    A(int n1,int n2):num1(n1),num2(n2){};
    int num1;
    int num2;
    operator int();//用户定义的转换类型
};
//外部的重载 非成员函数的重载
A operator+(const A& a,const A &b)
{
    return  A(a.num1+b.num1,a.num2+b.num2);;
}
int main()
{
   A a(1,2);
   A b(3,4);
   A c(a+b);
/*
member-candidates: none 不是，智能外部寻求了
non-member candidates: operator+(a, b) 有
built-in candidates: int(a) + int(b) 存在类型转换吗
overload resolution chooses operator+(a, b)
*/

   std::cout<<c.num1<<c.num2<<std::endl;
}





