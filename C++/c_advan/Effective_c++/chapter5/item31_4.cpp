/*
个制作Handle class的办法是， 令Person成为一种特殊的abstract baseclass（抽象基类），
称为Interface class。 这种class的目的是详细一一描述derived classes的接口（见条款34)， 
因此它通常不带成员变量， 也没有构造函数，只有一个virtual析构函数（见条款7)以及一组pure virtual函数， 
用来叙述整个接口。

Interface classes类似Java和 ．NET的Interfaces, 但C++的Interface classes 
并不需要负担Java和．NET的Interface所需负担的责任。举个例子，Java和 ．NET 
都不允许在Interfaces内实现成员变量或成员函数，但C++不禁止这两样东西。
C++ 这种更为巨大的弹性有其用途， 因为一如条款36所言， “non-virtual函数的实现 
“ 对继承体系内所有classes都应该相同， 所以将此等函数实现为Interface class（其中写有相应声明）的一部分也是合理的。

*/
#include<memory>
#include"string"
class Person{
public:
    virtual ~Person();
    virtual std::string name()const=0;
    virtual std::string birthDate()const=0;
    virtual std::string address()const=0;
};
/*
这个class的客户必须以Person的pointers和references来撰写应用程序，因为它不可能针对 “内含pure virtual函数”
的Person classes具现出实体。（然而却有可能对派生自Person的classes具现出实体， 详下。 ）
就像Handle classes的客户一样除非Interface class的接口被修改否则其客户不需重新编译

Interface class的客户必须有办法为这种class创建新对象。 他们通常调用一个 
特殊函数，此函数扮演 “真正将被具现化” 的那个 derived classes的构造函数角色。
这样的函数通常称为factory（工厂）函数（见条款13)或virtual 构造函数。 
它们返回指针（或更为可取的智能指针， 见条款18)， 指向动态分配所得对象，
而该对象支持 Interface class 的接口。这样的函数又往往在Interface class内被声明为 static: 

*/
class Person{
public:
    //返回一个shared_ptr，指向一个新的Person，并以给定之参数初始化，
    static std::shared_ptr<Person> create(const std::string&name,
                                        const Date&birthday,
                                        const Address&addr);
    virtual ~Person();
    virtual std::string name()const=0;
    virtual std::string birthDate()const=0;
    virtual std::string address()const=0;
};