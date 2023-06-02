/*
以对象管理资源
*/
#include<memory>
#include<string>
class Investment{
public:
    Investment();
    Investment(Investment*p1):pointer(p1){};
private:
    Investment*pointer;
}; //基类 root class
Investment* createInvestment()
{
    Investment*p=new Investment();
    return p;
}
void f()
{
    Investment *pInv=createInvestment();

    delete pInv;
}
void f1()
{
    std::auto_ptr<Investment>pInv(createInvestment());
    //调用factory函数，经由auto_ptr的析构函数自动删除
    std::auto_ptr<Investment>pInv2(pInv);//现在pInv2指向对象，pInv被设为null
    pInv2=pInv;////现在pInv2指向对象，pInv被设为null 相当于unqiue_ptr
}
void f()
{
    std::shared_ptr<Investment> pInv(createInvestment());//带有引用计数的智能指针
}
void f1()
{
    //这种指针目前的析构函数中没有delete[] 所以把会出错，在C++11 是没有问题的
    std::auto_ptr<std::string> aps(new std::string[10]);//error 
    std::shared_ptr<int> spi(new int[1024]);
}