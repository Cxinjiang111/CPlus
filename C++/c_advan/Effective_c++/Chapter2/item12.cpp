/*复制对象时勿忘其每一个成分

Copying函数应该确保复制 “对象内的所有成员变量” 及 “所有baseclass成分 “ 。
不要尝试以某个copying函数实现另一个copying函数。应该将共同机能放进第三 个函数中， 并由两个coping函数共同调用。
*/
#include<string>
#include<iostream>
class Date{};
void logCall(const std::string&funcName)
{
    std::cout<<funcName<<std::endl;
}
class Customer{
public:
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
/*
这时候既有的copying函数执行的是局部拷贝(partialcopy)： 它们的确复制了顾客的name,
但没有复制新添加的lastTransaction。大多数编译器对此不出任何怨言一—即使在最高警告级别中（见条款53)。
这是编译器对 “你自己写出copying 函数” 的复仇行为：既然你拒绝它们为你写出copying函数，
如果你的代码不完全，它们也不告诉你。结论很明显：如果你为class添加一个成员变量，
你必须同时修改copying函数。（你也需要修改class的所有构造函数（见条款4和条款45)以及任 
何非标准形式的operator=（条款IO有个例子）。 如果你忘记， 编译器不太可能提醒你。 ）

*/
int main()
{
    Customer a("hello");
    Customer b(a);
//output 
//customer copy constructor  这个危机还没有显示 
    return 0;
}



