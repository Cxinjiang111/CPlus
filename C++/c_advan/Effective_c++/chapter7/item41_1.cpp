#include<iostream>
class Widget{
public:
    //以下为显式接口
    Widget();
    virtual ~Widget();
    virtual std::size_t size() const;
    virtual void normalize();
    void swap(Widget&other);
};
/*
其public接口由一个构造函数、一个析构函数、 函数size,normalize,swap及
其参数类型、返回类型、常量性(constnesses)构成。 当然也包括编译器产生的copy 
构造函数和copy assignment操作符（见条款5)。 另外也可以包括typedefs,
以及如果你大胆违反条款22（令成员变量为private)而出现的public成员变量。

隐式接口就完全不同了，它并不基于函数签名式，而是有效表达式组成
*/
template<typename T>
void doProcessing(T&w)
{
    if(w.size()>10&&w!=someNastyWidget){

    }
    //T(w的类型)的隐式接口看来好像有这些约束
}
/*
    他必须提供一个名为size的成员函数，该函数返回一个整数值
    它必须支持一个operator！=函数 用来比较两个T对象，这里我们假设someNastyWidget的类型为T

真要感谢操作符重载(operator overloading)带来的可能性，这两个约束都不
需要满足。是的，T必须支持size成员函数，然曲这个函数也可能从base class继承而得。这个成员函数不需返回
一个整数值，甚至不需返回个数值类型。就此而言，它甚至不需要返回
个定义有operator>的类型！它唯需要做的是返回一个类型为x的对象，而x对象加上一个
个int(10的类型）必须能够调用一个operator>。这个operator>不需要非得取得一个类型为x的参数不可，
 因为它也可以取得类型Y的参数，只要存在一个隐式转换能够将类型X的对象转换为类型Y的对象

同样道理，T并不需要支持operator＝! ，因为以下这样也是 可以的：operator!=
接受一个类型为 x 的对象和 -个类型为y的对象， T可被转换为 x而
someNastyWidget的类型可被转换为Y,这样就可以有效调用operator!＝。
*/