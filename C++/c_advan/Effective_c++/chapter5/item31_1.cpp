
namespace std{
    class string;
}
class Date;
class Address;
class Person{
public:
    Person(const std::string&name,const Date&birthday,const Address&addr);
    std::string name()const;
    std::string birthDate()const;
    std::string address()const;
};
/*
如果可以那么做， Person的客户就只需要在Person接口被修改过时才重新编译。
个想法存在两个问题。 第一 ， string不是个class, 它是个typedef（定义为 basic_string<char>)。 
因此上述针对s七ring而做的前置声明并不正确；正确的 前置声明比较复杂， 因为涉及额外的templates。
然而那并不要紧， 因为你本来就不 该尝试手工声明一部分标准程序库。 你应该仅仅使用适当的五ncludes完成目的。 
标准头文件不太可能成为编译瓶颈，特别是如果你的建置环境允许你使用预编译头 文件(precompiled headers)。
如果解析(parsing)标准头文件真的是个问题，你可 能需要改变你的接口设计， 
避免使用标准程序库中 “ 引发不受欢迎之＃includes"那一部分

关千 “前置声明每一件东西 ” 的第二个（同时也是比较重要的）困难是， 编译器必须在编译期间知道对象的大小。 考虑这个：
*/
int main()
{
    int x;
    Person p();
}
/*
当编译器看到x的定义式， 它知道必须分配多少内存（通常位于stack内）才够持
有 个int。没问题， 每个编译器都知道一个int有多大。 当编译器看到p的定义
式， 它也知道必须分配足够空间以放置一个Person,但它如何知道一个Person对象有多大呢？
编译器获得这项信息的唯一办法就是询问class定义式。然而如果class 定义式可以合法地不列出实现细目，
编译器如何知道该分配多少空间？
*/