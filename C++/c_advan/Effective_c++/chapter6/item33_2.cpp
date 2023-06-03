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
    cout<<"base mf1   int a "<<endl;
}
void Base::mf3()
{
    cout<<"base mf3"<<endl;
}
void Base::mf3(double)
{
    cout<<"base mf3 double "<<endl;
}
class Derived:public Base{
public:
    //Derived(const int x,const int y):x1(x),Derived::Base(y){};
    Derived(Base &b):Derived::Base(b){};
    Derived();
    using Base::mf1;//提供可见基类的框架
    using Base::mf3;
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
    mf1(2); //虚函数基类中的error Derived::mf1遮掩了Base::mf1
    mf1();
    mf2();
    mf3();
    mf3(3.0); ///error 非虚函数基类中的error Derived::mf1遮掩了Base::mf1
}
int main()
{
    Derived d;
    d.mf4();
/*输出
base mf1   int a 
derived mf1
derived mf2
derived mf3
base mf3 double 
*/
    return 0;
}

