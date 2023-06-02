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
    //explicit 阻止他们被用来执行隐式类型转换 
    //但他们仍可用来进行显式类型转换
    explicit B(int x=0,bool b=true)
    {
        cout<<"explicit B()  X:"<<x<<endl;
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
    //dosomething(28);//编译不过去
    cout<<"=========="<<endl;
    dosomething(B(34));
/*
explicit B()  X:0
dosomething B
==========
explicit B()  X:28
dosomething B
==========
explicit B()  X:34
dosomething B
*/
    return 0;
}