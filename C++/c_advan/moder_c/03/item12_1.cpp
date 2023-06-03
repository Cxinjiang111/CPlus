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
    virtual void mf1()const{
        cout<<"Base mf1()const"<<endl;
    }
    virtual void mf2(int x){
         cout<<"Base  mf2(int x)"<<endl;
    }
    virtual void mf3()&{
        cout<<"Base mf3()&"<<endl;
    }
    void mf4()const{
        cout<<"Base mf4()const"<<endl;
    }
};
class Derived:public Base{
public:
    virtual void mf1(){
        cout<<"Derived mf1()"<<endl;
    }
    virtual void mf2(unsigned int x){
        cout<<"Derived mf2(unsigned int x)"<<endl;
    }
    virtual void mf3()&&{
        cout<<"Derived mf3()&&"<<endl;
    }
    void mf4()const{
        cout<<"Derived mf4()const"<<endl;
    }
};
int main(){
    std::unique_ptr<Base> upb=std::make_unique<Derived>();
    upb->mf1();  //Base mf1()const
    upb->mf2(5);//Base  mf2(int x)
    upb->mf3();//Base mf3()&
    upb->mf4();//Base mf4()const
  //全部会调用基类，也就是说上述的继承是失败的。



    return 0;
}