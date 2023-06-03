#include<string>
#include<memory>
class PersonImpl;
class Date;
class Address;
class Person{
public:
    Person(const std::string &name,const Date&birthday,const Address&addr);
    std::string name()const;
    std::string birthDate()const;
    std::string address()const;
private:
    std::shared_ptr<PersonImpl>pImpl;
};
/*
这样的设计之下，Person的客户就完全与Dates, Addresses以及Persons的实现细目分离了。
那些classes的任何实现修改都不需要Person 客户端重新编译。 此外由千客户无法看到Person的实现细目，
 也就不可能写出什么 “取决千那些细目 “ 的代码。 这真正是 “接口与实现分离 ” !

这个分离的关键在千以 “ 声明的依存性” 替换 “ 定义的依存性” ，那正是编译 依存性最小化的本质：
现实中让头文件尽可能自我满足， 万一做不到， 则让它与其他文件内的声明式（而非定义式）相依。
其他每一件事都源自千这个简单的设计策略：

如果使用object references或object pointers可以完成任务， 就不要使用 objects。
你可以只靠一个类型声明式就定义出指向该类型的references和 pointers;
但如果定义某类型的objects, 就需要用到该类型的定义式。

如果能够，尽量以class声明式替换class定义式。注意，当你声明一个函数而它用到某个class时，
你并不需要该class的定义；纵使函数以by value方式传递该类型的参数（或返回值）亦然：
*/
class Date;
Date today();
void clearAppointments(Date d);
/*
当然，pass-by-value一般而言是个糟糕的主意（见条款20)，但如果你发现因为某种因素被迫使用它， 
并不能够就此为“非必要之编译依存关系”导入正当性。

声明today函数和clearAppointrnents函数而无需定义Date,这种能力可 能会令你惊讶，但它并不是真的那么神奇。
 一旦任何人调用那些函数，调用之前Date定义式一定得先曝光才行。那么或许你会纳闷，何必费心声明一个没人 
 调用的函数呢？嗯，并非没人调用，而是并非每个人都调用。假设你有一个函 数库内含数百个函数声明，
 不太可能每个客户叫遍每一个函数。如果能够将“ 提供class定义式”（通过五nclude完成）的义务从“函数声明所在” 之头文 
 件移转到“内含函数调用”之客户文件，便可将“并非真正必要之类型定义”与客户端之间的编译依存性去除掉。


*/