#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
using namespace std;
/*
这么多的重写需求意味着哪怕⼀个小小的错误也会造成巨⼤的不同。
代码中包含重写错误通常是有效的，但它的意图不是你想要的。因此你不能指望当你犯错时编译器能通
知你。⽐如，下⾯的代码是完全合法的，咋⼀看，还很有道理，但是它包含了⾮虚函数重写。你能识别
每个case的错误吗，换句话说，为什么派⽣类函数没有重写同名基类函数？
*/

/*
mf1在基类声明为const ,但是派⽣类没有这个常量限定符
mf2在基类声明为接受⼀个int参数，但是在派⽣类声明为接受unsigned int参数
mf3在基类声明为左值引⽤限定，但是在派⽣类声明为右值引⽤限定
mf4在基类没有声明为虚函数
你可能会想，“哎呀，实际操作的时候，这些warnings都能被编译器探测到，所以我不需要担⼼。”
可能你说的对，也可能不对。就我⽬前检查的两款编译器来说，这些代码编译时没有任何
warnings，即使我开启了输出所有warnings（其他编译器可能会为这些问题的部分输出
warnings，但不是全部） 确实有其mf4函数不报错，有点坑
*/
class Base{
public:
    virtual void mf1() {
        cout<<"Base mf1()const"<<endl;
    }
    virtual void mf2(int x){
         cout<<"Base  mf2(int x)"<<endl;
    }
    virtual void mf3()&{
        cout<<"Base mf3()&"<<endl;
    }
    virtual void mf4()const{
        cout<<"Base mf4()const"<<endl;
    }
};
//以下是全部明确的添加override 使其重载
class Derived:public Base{
public:
    virtual void mf1()override{
        cout<<"Derived mf1()"<<endl;
    }
    virtual void mf2( int x)override{
        cout<<"Derived mf2( int x)"<<endl;
    }
    virtual void mf3()& override{
        cout<<"Derived mf3()&"<<endl;
    }
    void mf4()const override{
        cout<<"Derived mf4()const"<<endl;
    }
};
class Derived_1:public Base{
public:
    virtual void mf1(){
        cout<<"Derived_1 mf1()"<<endl;
    }
    virtual void mf2( int x){
        cout<<"Derived_1 mf2( int x)"<<endl;
    }
    virtual void mf3()& {
        cout<<"Derived_1 mf3()&"<<endl;
    }
    void mf4()const{
        cout<<"Derived_1 mf4()const"<<endl;
    }
};
void t1(){
       std::unique_ptr<Base> upb=std::make_unique<Derived>();
    upb->mf1();
    upb->mf2(5);
    upb->mf3();
    upb->mf4(); 
    //output
    //Derived mf1()
    //Derived mf2( int x)
    //Derived mf3()&
    //Derived mf4()const
}
void t2(){
    std::unique_ptr<Base> upb=std::make_unique<Derived_1>();
    upb->mf1();
    upb->mf2(5);
    upb->mf3();
    upb->mf4(); 
    /*
Derived_1 mf1()
Derived_1 mf2( int x)
Derived_1 mf3()&
Derived_1 mf4()const
    */
   /*
   其实正确书写继承与基类函数，调用规则是一样的，不过当你不小心，或者以为可以但事实上并不能
   构成继承重载是，override会让编译器明确告诉你你错了，所以非常推荐在继承类的函数后加override关键字
   */
}
int main(){

    t2();
    return 0;
}