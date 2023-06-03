#include<iostream>
using namespace std;
//实函数为编译期确定内存
class Base{
    private:
        //private 对virtual与非virtual没啥影响
        virtual void display(){cout<<"Base virtual  display"<<endl;}//虚基类
        void say(){cout<<"Base say"<<endl;}//实函数
    public:
        void f2(){cout<<"Base no override or no virtual "<<endl;}
        virtual void func(){cout<<"Base func()"<<endl;}//虚函数
        void f1(string a){cout<<"Base f1(string)"<<endl;}//两个f1()重载的   
        void f1(int a){cout<<"Base f1(int)"<<endl;}
};
class Derived:public Base{
    public:
        void dispaly(){cout<<"DerivedA diaplay()"<<endl;}//实函数可能覆盖基类
        void f1(int a,int b){cout<<"DerivedA f1(int,int)"<<endl;}//实函数
        void say(){cout<<"Derived say()"<<endl;}//实函数
        virtual void func(){cout<<"DerivedA func()"<<endl;}
};
int main(){
    //
    Derived a;//构造A继承类的同时，会实现覆盖和对基类同名函数的覆盖，
    Base *b=&a;
    //基类指针指向继承类 那么a只有内存 对b可见的只有a的可见成员
    b->f1("hello");//这里构造了A  
    b->f1(3);
    b->func();
    //
    cout<<"called -------------"<<endl;
    //这里内存结构会不会把基类的同名函数给覆盖掉这个
    a.f1(5,3); 
    a.func();
    a.f2();

    Derived *a1=new Derived();
    Base *b1=a1;
    //
    a1->dispaly();
    a1->say();
    a1->f1(3,5);
    a1->func();
    a1->f2();
    /*
    Base f1(string)
    Base f1(int)
    DerivedA func()
    called -------------
    DerivedA f1(int,int)
    DerivedA func()
    Base no override or no virtual 
    DerivedA diaplay()
    Derived say()
    DerivedA f1(int,int)
    DerivedA func()
    Base no override or no virtual 
    */
}
