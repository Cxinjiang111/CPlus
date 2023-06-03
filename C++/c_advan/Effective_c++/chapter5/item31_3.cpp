/*
为声明式和定义式提供不同的头文件。为了促进严守上述准则，需要两个头文件， 
一个用千声明式，个用于定义式。当然，这些文件必须保持一致性， 如果有个声明式被改变了，
两个文件都得改变。因此程序库客户应该总是＃include 一个声明文件而非前置声明若干函数，
程序库作者也应该提供这两个头文件。举个例子，Date的客户如果希望声明today和clearAppointments,
他们不该 像先前那样以手工方式前置声明Date,而是应该＃include适当的、 内含声明 式的头文件：

*/
// #include"datefwd.h" //该头文件申明了Date的声明式
// Date today();
// void clearAppointments(Date d);

/*
像Person这样使用pimpl idiom的classes, 往往被称为Handle classes。也许 你会纳闷，
这样的classes如何真正做点事情。办法之一是将它们的所有函数转交给 
相应的实现类(implementationclasses)并由后者完成实际工作。例如下面是Person 两个成员函数的实现：
*/
#include"Person.h"
Person::Person(const std::string&name,const Date&birthday,const Address&addr):pImpl(new PersonImpl(name,birthday,addr)){
};
std::string Person::name()const{
    return pImpl->name();
}

/*
请注意， Person构造函数以new（见条款16)调用Personimpl构造函数， 以及Person:: name函数内调用Personirnpl: : name。
 这是重要的， 让Person变成—个Handle class并不会改变它做的事， 只会改变它做事的方法。

*/