#include<iostream>
using namespace std;
class A{
    public:
    A(){ //默认构造函数 
        cout<<"A()"<<endl;
    }
};
class B{
public:
    //explicit 阻止他们被用来执行隐式类型转换 但他们仍可用来进行显式类型转换
     B(int x=0,bool b=true)
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
    //A a;

    B bobj1;
    dosomething(bobj1);
    cout<<"=========="<<endl;
    B bobj2(28);
    cout<<"=========="<<endl;
    dosomething(28); //这边并没有加explicit 那么我传入一个非B类型，程序依然可运行，但实际是个错误的
    //加了explicit关键字，编译就会报错提示，不能发生转换
    cout<<"=========="<<endl;
    dosomething(B(34));
/*
output
 B()  X:0
dosomething B
==========
 B()  X:28
dosomething B
==========
 B()  X:34
dosomething B
*/
    return 0;
}