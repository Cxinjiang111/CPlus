#include<iostream>
#include<array>
using namespace std;
class Base
{
public:
    Base();
    virtual ~Base();
};
Base::Base(){}
Base::~Base(){}
class A:public Base
{
public:
    A(){cout<<"A constructor"<<endl;}
    ~A(){}
};
class B:public Base
{
public:
    B(){cout<<"B constructor"<<endl;}
    ~B() {}
    Base *add(Base *base){
        return new B();}
};
enum  TYPE
{
    TOOL_A,
    TOOL_B,
    TOOL_NUM
};
class C
{
private:
    std::array<Base*,TYPE::TOOL_NUM> pbase;
public:
    C();
    Base *create(int index)
    {
        return pbase[index]; 
    }
};
C::C()
{    
    //这样就不用switch 先全部注册好，则传入一个索引就可以返回一个对象
    std::array<Base*,TYPE::TOOL_NUM> pbase;
    pbase[0]=new B();
    pbase[1]=new A();
}

int main()
{




}


