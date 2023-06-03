#include<iostream>
#include<string>
class Widget{
public:
    Widget(Widget&&rhs):s(std::move(rhs.s)){
        ++moveCtrocalls;
    }

private:
    static std::size_t moveCtrocalls;
    std::string s;
};
class Widget{
public:
    Widget(Widget&&rhs):s(std::forward<std::string>(rhs.s)){
        ++moveCtrocalls;
    }

private:
    static std::size_t moveCtrocalls;
    std::string s;
};
/*
注意，第⼀，std::move只需要⼀个函数参数(rhs.s)，而std::forward不但需要⼀个函数参数
(rhs.s)，还需要⼀个模板类型参数std::string。其次，我们转发给std::forward的参数类型应当是
⼀个⾮引⽤(non-reference)，因为传递的参数应该是⼀个右值（⻅ Item 28)。 同样，这意味着
std::move⽐起std::forward来说需要打更少的字，并且免去了传递⼀个表⽰我们正在传递⼀个右值
的类型参数。同样，它根绝了我们传递错误类型的可能性，（例如，std::string&可能导致数据成员
s被复制而不是被移动构造）

更重要的是，std::move的使⽤代表着⽆条件向右值的转换，而使⽤std::forward只对绑定了右值的
引⽤进⾏到右值转换。这是两种完全不同的动作。前者是典型地为了移动操作，而后者只是传递（亦作
转发）⼀个对象到另外⼀个函数，保留它原有的左值属性或右值属性。因为这些动作实在是差异太⼤，
所以我们拥有两个不同的函数（以及函数名）来区分这些动作。

*****
std::move执⾏到右值的⽆条件的转换，但就⾃⾝而⾔，它不移动任何东西。
std::forward只有当它的参数被绑定到⼀个右值时，才将参数转换为右值。
std::move和std::forward在运⾏期什么也不做

*/