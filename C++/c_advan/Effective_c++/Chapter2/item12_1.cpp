#include<string>
#include<string>
#include<iostream>
class Date{};
void logCall(const std::string&funcName)
{
    std::cout<<funcName<<std::endl;
}
class Customer{
public:
    //Customer();此时编译器不会替你生成，
    Customer(std::string Name):name(Name){};
    Customer(const Customer &rhs);
    Customer&operator=(const Customer&rhs);
private:
    std::string name;
    Date lastTransaction;//并没有在自己写的copying类函数中进行参数复制
};
// Customer::Customer(const Customer &rhs):name(rhs.name)
// {
//     logCall("customer copy constructor");
// }
Customer&Customer::operator=(const Customer&rhs)
{
    logCall("customer copy assignment operator");
    this->name=rhs.name;
    return *this;
}
class PriorityCustomer:public Customer{
public:
    PriorityCustomer(const PriorityCustomer &rhs);
    PriorityCustomer&operator=(const PriorityCustomer &rhs);
private:
    int priority;
};
//这么写error  类不存在Customer默认构造函数
//之所以会有这样的错误，就是 3 5法则决定 你自己写了copying 那么你就得五个全写，要么你就全不写，编译器来自己写
PriorityCustomer::PriorityCustomer(const PriorityCustomer&rhs):priority(rhs.priority)
{
    logCall("priorityCustomer copy constructor");
}
/*
PriorityCustomer的copying币数看起来好像复制了PriorityCustomer内的每样东西，但是请再看一眼。是的，
它们复制了PriorityCustomer声明的成员变量，但每个PriorityCustomer还内含它所继承的Customer成员变屈复件（副本），
 曲那些成员变量却未被复制。PriorityCustomer的copy构造函数并没有指定实参传给其base class构造函数
 （也就是说它在它的成员初值列(member initialization list)中 没有提到Customer)，
 因此PriorityCustomer对象的Customer成分会被不带实参之Cus七omer构造函数（即default构造函数必定有一个否则无法通过编译）初始化。
  default构造函数将针对name和lastTransacLlon执行缺省的初始化动作。
*/
PriorityCustomer&PriorityCustomer::operator=(const PriorityCustomer &rhs)
{
    logCall("priorityCustomer copy operator =");
    this->priority=rhs.priority;
    return *this;
}



