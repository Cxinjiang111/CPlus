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
Customer::Customer(const Customer &rhs):name(rhs.name)
{
    logCall("customer copy constructor");
}
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
//解决上述问题就是显示这里显式调用基类构造函数，Customer(rhs)
PriorityCustomer::PriorityCustomer(const PriorityCustomer&rhs):Customer(rhs),priority(rhs.priority)
{
    logCall("priorityCustomer copy constructor");
}

PriorityCustomer&PriorityCustomer::operator=(const PriorityCustomer &rhs)
{
    logCall("priorityCustomer copy operator =");
    Customer::operator=(rhs);//显式的调用
    this->priority=rhs.priority;
    return *this;
}
/*
本条款题目所说的“ 复制每一个成分“现在应该很清楚了。当你编写一个copying函数， 
请确保（1)复制所有local成员变量，（2)调用所有base classes内的适当的 copying函数。

这两个copying函数往往有近似相同的实现本体，这可能会诱使你让某个函数调 用另一个函数以避免代码重复。
这样精益求精的态度值得赞赏， 但是令某个copying 函数调用另一个copying函数却无法让你达到你想要的目标。

令copyassignment操作符调用copy构造函数是不合理的，因为这就像试图构造 一个已经存在的对象。
这件事如此荒谬， 乃至千根本没有相关语法。 是有一些看似 如你所愿的语法， 但其实不是；
也的确有些语法背后真正做了它， 但它们在某些情况下会造成你的对象败坏， 所以我不打算将那些语法呈现给你看。
单纯地接受这个叙述吧：你不该令copyassignment操作符调用copy构造函数。

反方向一令copy构造函数调用copyassignment操作符—􀁖同样无意义。构造 函数用来初始化新对象， 
而assignment操作符只施行千已初始化对象身上。 对一个尚未构造好的对象赋值， 就像在一个尚未初始化的对象身上做
“只对已初始化对象才有意义” 的事一样。 无聊嘛！别尝试。


如果你发现你的copy构造函数和copyassignment操作符有相近的代码，消除重复代码的做法是，
建立一个新的成员函数给两者调用。 这样的函数往往是private而 且常被命名为init。 
这个策略可以安全消除copy构造函数和copy assignment操作 符之间的代码重复。
*/


