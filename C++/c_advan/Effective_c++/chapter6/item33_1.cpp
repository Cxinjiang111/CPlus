#include<iostream>
using namespace std;
class Base{
private:
    int x;
public:
    Base();
    Base(const int x_1):x(x_1){};
    virtual void mf1()=0;
    virtual void mf1(int);
    virtual void mf2();
    void mf3();
    void mf3(double);
    ~Base(){};
};
Base::Base()
{}
void Base::mf2()
{
    cout<<"base mf2"<<endl;
}
void Base::mf1()
{
    cout<<"base mf1"<<endl;
}
void Base::mf1(int a)
{
    cout<<"base mf1   a"<<endl;
}
class Derived:public Base{
public:
    //Derived(const int x,const int y):x1(x),Derived::Base(y){};
    Derived(Base &b):Derived::Base(b){};
    Derived();
    virtual void mf1();//与基类重名
    void mf2()override;
    void mf3();
    void mf4();
    ~Derived(){};
private:
    int x1;
};
void Derived::mf1()//与基类重名
{
    cout<<"derived mf1"<<endl;
}
Derived::Derived()
{}
void Derived::mf2()
{
    cout<<"derived mf2"<<endl;
}
void Derived::mf3()
{
    cout<<"derived mf3"<<endl;
}
void Derived::mf4(){ 
   // mf1(2); 虚函数基类中的error Derived::mf1遮掩了Base::mf1
    mf1();
    mf2();
    mf3();
   // mf3(3); error 非虚函数基类中的error Derived::mf1遮掩了Base::mf1
}
/*
这些行为背后的基本理由是为了防止你在程序库或应用框架(application framework)
内建立新的derivedclass时附带地从疏远的baseclasses继承重载函数。 不幸的是你通常会想继承重载函数。
实际上如果你正在使用public继承而又不继承那些重载函数，就是违反base和derivedclasses之间的is-a关系，
而条款32说过 is-a是public继承的基石。囚此你几乎总会想要推翻(override)C+＋对“继承而来的名称＂的缺省遮掩行为。
*/
int main()
{
    Derived d;
    d.mf4();

    return 0;
}

