/*
再资源管理类中提供对原始
结论：
APis往往要求访问原始资源(raw resources)，所以每一个RAIi class应该提供一个 “取得其所管理之资源” 的办法。
对原始资源的访问可能经由显式转换或隐式转换。 一般而言显式转换比较安全， 但隐式转换对客户比较方便。
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
int daysHeld(const Investment *pi);
int main()
{
    std::shared_ptr<Investment> pInv(createInvestment());
    //int days=daysHeld(pInv);//编译通不过 但我想传个指针进去 
    //不存在从 "std::shared_ptr<Investment>" 到 "const Investment *" 的适当转换函数C/C++(413)

//解决方法1  
 int days=daysHeld(pInv.get());//转化为不带类型的指针 将pInv内的原始指针传给daysHeld

//2.


}