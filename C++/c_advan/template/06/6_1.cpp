//assignable 
//一个身为assignable model 的型别，没有必要同时也是equality comparable 的model 
//因为它可以不需要任何operator==
/*
copy constructor
X(x)
x
返回型别    X
必然结果    X(x)是 x的复制品
copy constructor
X x(y)
X x=y
必然结果： x是y的复制品

assignment
x=y
返回结果    X&
必然结果    x是y的复制品
*/
/* default constructible 默认构造函数
*
X();
or
X x;


*/
#include<iostream>
using namespace std;
class A{

int a;
};
int main()
{
    A a=A();//不一定有效表达式，因为它用到了一个copy constructor 

    return 0;
}