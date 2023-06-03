/*
equality comparable
operator== 系表示等价关系的话，该型别便是equality comparable 

相等性
x==y
返回型别：任何可转换为bool的型别
先决条件：x和y必须在operator==的domain内，
具有的特性
invariant 恒常型
&x=&y 为x==y     这个&为引用而非取地址传参的过程中，是引用传值而非指针
x==x
x==y y==x
x==y y==z  => x==z
*/
#include<iostream>
using namespace std;
class A{
public:

    bool operator==(const A& val)
    {
        return val.m_a==m_a&&val.m_b==m_b;
    }
int m_a;
int m_b;
};
void t1(A &a,A &b)
{
    if(a==b)
    {
        cout<<"ok"<<endl;
    }
    else{
        cout<<"no ok"<<endl;
    }
}
int main()
{
    A a;
    a.m_a=1;
    a.m_b=2;
    A b;
    b.m_a=1;
    b.m_b=2;
    A c(a);
    t1(a,b); 



    return 0;
}