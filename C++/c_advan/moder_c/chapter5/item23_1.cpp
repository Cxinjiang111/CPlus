#include<iostream>

// class String{
// public:
//     String(String&&rhs);//移动构造函数
//     String(const String&rhs);//复制构造函数

// };
/*
在类Annotation的构造函数的成员初始化列表(member initialization list)中，std::move(text)的结
构是⼀个const std::string的右值。这个右值不能被传递给std::string的移动构造函数，因为移
动构造函数只接受⼀个指向⾮常量(non-const) std::string的右值引⽤。然而，该右值却可以被传递
给std::string的复制构造函数，因为指向常量的左值引⽤允许被绑定到⼀个常量右值上。因此，
std::string在成员初始化的过程中调⽤了复制构造函数，即使text已经被转换成了右值。这样是为
了确保维持常量属性的正确性。从⼀个对象中移动（Moving)出某个值通常代表着修改该对象，所以语
⾔不允许常量对象被传递给可以修改他们的函数（例如移动构造函数）。

在传递的过程中，由于带有左值在转换的过程中带有const属性，那么右值也带有const属性，而在选择构造函数时move操作
又不能对带有const属性的值进行操作，因此只能选择复制构造函数    但是为啥这么绕着想干嘛呢？？？不懂
*/
/*
从这个例⼦中，可以总结出两点。很好
第⼀，不要在你希望能移动对象的时候，声明他们为常量。对常量对象的移动请求会悄⽆声息的被转化为复制操作。
第⼆点，std::move不仅不移动任何东西，而且它也不保证它执⾏转换的对象可以被移动。
关于std::move，你能确保的唯⼀⼀件事就是将它应⽤到⼀个对象上，你能够得到⼀个右值。总结到位
*/
class widget{
public:
    widget();
    widget&(widget &);
    widget(widget&&);

};
void process(const widget& lvalArg); //左值处理
void process(widget&& rvalArg); //右值处理
template <typename T> //⽤以转发参数到process的模板
void logAndProcess(T&& param)
{
auto now = //获取现在时间
std::chrono::system_clock::now();
makeLogEntry ("calling 'process",now);
process(std::forward<T>(param));
}
void t1(){
    Widget w;
logAndProcess(w); //call with lvalue
logAndProcess(std::move(w)); //call with rvalue
}
