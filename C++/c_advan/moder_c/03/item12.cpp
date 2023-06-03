#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
using namespace std;
class Base{
public:
    virtual void dowork_1();
    //
    virtual void dowork()&;//只有*this为左值的时候才能被调⽤
    virtual void dowork()&&;//只有*this为右值的时候才能被调⽤
    //、、
    virtual void dowork_3()const;
};
class Derived:public Base{
public:
    //virtual void dowork();//  这个继承而来的virtual可写可不写
     void dowork_1();//  这个继承而来的virtual可写可不写
     void dowork_3();
};
void Base::dowork_1(){
    cout<<"Base::dowork()"<<endl;
}
void Base::dowork()&{
    cout<<"Base::dowork()&"<<endl;
}
void Base::dowork()&&{
    cout<<"Base::dowork()&&"<<endl;
}
void Derived::dowork_1(){
    cout<<"Derived::dowork()"<<endl;
}
void Base::dowork_3()const{
    cout<<"Base::dowork_3()const"<<endl;
}
void Derived::dowork_3(){
    cout<<"Derived::dowork_3()"<<endl;
}
void t1(){
    std::unique_ptr<Base> upb=std::make_unique<Derived>();//基类指针指向创建的父类对象
    upb->dowork_1();//output :  Derived::dowork()
}
void t2(){
    Base b;
    //可以解释上述左值与右值调用规则
    b.dowork();           //output--->   Base::dowork()&
    std::move(b).dowork();//output--->   Base::dowork()&&
}
void t3(){
    std::unique_ptr<Base> upb=std::make_unique<Derived>();
    upb->dowork_3();//output    Base::dowork_3()const
    //这里不会调用继承类的函数，因为没有const
}
int main(){
   // t1();
   // t2();
   t3();
    return 0;
}
