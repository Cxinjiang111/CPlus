/*运用成员函数模板接受所有兼容类型
*/
/*
真实指针做的很好的就是支持隐式转换，derived class 可以隐式转换为base class指针，
指向 non-const对象的指针可以转换为指向const对象。
*/
#include<memory>
class Top{};
class Middle:public Top{};
class Bottom:public Middle{};
void f()
{
    Top *pt1=new Middle;
    Top *pt2=new Bottom;
    const Top*pct2=pt1;
}
template<typename T>
class SmartPtr{
public:
    explicit SmartPtr(T*realPtr);
    
};
void f1()
{
    std::shared_ptr<Top> p1=std::make_shared<Middle>(new Middle);//p1的类型从Middle 转换为Top 只是智能指针的类型转换
}


