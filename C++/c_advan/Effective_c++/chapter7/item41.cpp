/*了解隐式接口和编译期多态
classes和templates都支持接口(interfaces)和多态(polymorphism)。
对classes而言接口是显式的(explicit)，以函数签名为中心。多态则是通过virtual 函数发生千运行期。
对template参数而言，接口是隐式的(implicit)，奠基千有效表达式。 
多态则是通过template具现化和函数重载解析(function overloading resolution)发生于 编译期。
*/
#include<iostream>
class Widget{
public:
    Widget();
    virtual ~Widget();
    virtual std::size_t size() const;
    virtual void normalize();
    void swap(Widget&other);
};
//--通过传递类对象来调用接口函数，功能函数
void doProcessing(Widget&w)
{
    Widget temp(w);
    temp.normalize();
    temp.swap(w);
}
/*
由于w 的类型被声明为 Widget, 所以 w 必须支持Widget接口。 
我们可以在源码中找出这个接口（例如在阳dget的．h文件中），看看它是什么样子，所以我 一
称此为个显式接口 (explicit interface)，也就是它在源码中明确可见。

由于Widget的某些成员函数是virtual, w对那些函数的调用将表现出运行期多
态(runtime polymorphism)，也就是说将千运行期根据 w的动态类型
决定究竟调用哪一函数。
*/


/*
Templates及泛型编程的世界，与面向对象有根本上的不同。在此世界中显式接口和运行期多态仍然存在， 
但重要性降低。反倒是隐式接口(implicit interfaces)和编译期多态(compile-time polymorphism) 
移到前头了。若想知道那是什么，看看当我们将doProcessing从函数转变成函数模板(function template)时发生什么事：

*/

template<typename T>
void doProcessing(T &w)
{
    T temp(w);
    temp.normalize();
    temp.swap(w);
}
/*
w必须支持哪一种接口，系由template中执行于w身上的操作来决定。本例看来
w的类型 T 好像必须支持 size,norrnalize 和 swap 成员函数、 copy构造函数（用
以建立temp)、不等比较(inequality comparison,用来比较someNasty-Widget)。
我们很快会看到这并非完全正确，但对目前而言足够真实。重要的是，这一组表达式
（对此template而言必须有效编译）便是T必须支持的一组隐式接口(implicit interface)。

凡涉及w的任何函数调用，例如operator>和operator!＝，有可能造成template 
具现化(instantiated)，使这些调用得以成功。这样的具现行为发生在编译期。
“以不同的template参数具现化function templates”会导致调用不同的函数，
这 便是所谓的编译期多态(compile-time polymorphism)。

纵使你从未用过templates, 应该不陌生”运行期多态”和“编译期多态”之间的差异，
因为它类似于 “ 哪一个重载函数该被调用＂（发生在编译期）和“哪一个virtual函数该被绑定” 
（发生在运行期）之间的差异。显式接口和隐式接口的差异 就比较新颖，需要更多更贴近的说明和解释。

*/



