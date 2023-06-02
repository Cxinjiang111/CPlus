#include<iostream>
using namespace std;
class A{
    public:
    A(){ //默认构造函数 
        cout<<"A()"<<endl;
    }
};
class B:public A{
public:
    //explicit 阻止他们被用来执行隐式类型转换 
    //但他们仍可用来进行显式类型转换
    explicit B(int x=0,bool b=true)
    {
        cout<<" B()  X:"<<x<<endl;
    }
};
void dosomething(B objB)
{
    cout<<"dosomething B"<<endl;
}
int main()
{
    A a;

    cout<<"=========="<<endl;
    //dosomething(a); //编译不过

    return 0;
}