/*avoid hiding inherited names
避免隐藏继承而来的名称

derived classes内的名称会遮掩base classes内的名称。在public继承下从来没有 人希望如此。
为了让被遮掩的名称再见大日，可使用using声明式或转交函数(forwarding functions)。
*/
/*
因为derived classes继承了申明于base classes内的所有东西，实际运作方式是，
derived class 作用域被嵌套在base class作用域内，
*/
#include<iostream>
using namespace std;
class Base{
private:
    int x;
public:
    Base();
    Base(const int x_1):x(x_1){};
    virtual void mf1()=0;
    virtual void mf2();
    void mf3();
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
class Derived:public Base{
public:
    //Derived(const int x,const int y):x1(x),Derived::Base(y){};
    Derived(Base &b):Derived::Base(b){};
    Derived();
    virtual void mf1();//与基类重名
    //void mf2()override;
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
// void Derived::mf2()
// {
//     cout<<"derived mf2"<<endl;
// }
void Derived::mf4()
{
    mf2();//
    mf1();// 继承类中的mf1；
}
int main()
{
    Derived d;
    d.mf4();

    return 0;
}








