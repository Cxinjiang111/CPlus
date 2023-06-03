#include<iostream>
#include<vector>
class Widget{
public:
    Widget(Widget&&rhs):s(std::move(rhs.s)){
        ++moveCtrocalls;
    }

private:
    static std::size_t moveCtrocalls;
    std::string s;
};
void f(Widget&&param);//右值引⽤
Widget&&var1=Widget();//右值引⽤
auto var2=var1;         //不是右值引⽤
template<typename T>
void f(std::vector<T>&&param);//右值引⽤
template<typename T>
void f(T &&param); //不是右值引⽤
/*
事实上，T&&有两种不同的意思。第⼀种，当然是右值引⽤。这种引⽤表现得正如你所期待的那样: 它们
只绑定到右值上，并且它们主要的存在原因就是为了声明某个对象可以被移动。
T&&的第⼆层意思，是它既可以是⼀个右值引⽤，也可以是⼀个左值引⽤。这种引⽤在源码⾥看起来像
右值引⽤（也即T&& ),但是它们可以表现得它们像是左值引⽤(也即T& )。它们的⼆重性(dual nature)使
它们既可以绑定到右值上(就像右值引⽤)，也可以绑定到左值上(就像左值引⽤)。 此外，它们还可以绑定
到常量(const)和⾮常量(non-const)的对象上，也可以绑定到volatile和non-volatile的对象上，甚
⾄可以绑定到即const⼜volatile的对象上。它们可以绑定到⼏乎任何东西。这种空前灵活的引⽤值
得拥有⾃⼰的名字。我把它叫做通⽤引⽤(universal references)。（

*/
//类型推导会导致编译器自己推导的法则，并不一定按照锁期望的
template <typename T>
void f(T&& param); //param是⼀个通⽤引⽤
auto&& val2= var1; //var2是⼀个通⽤引⽤
/*
这两种情况的共同之处就是都存在类型推导(type deduction)。在模板f的内部，参数param的类型需
要被推导，而在变量var2的声明中，var2的类型也需要被推导。同以下的例⼦相⽐较(同样来⾃于上⾯
的⽰例代码)，下⾯的例⼦不带有类型推导。如果你看⻅T&&不带有类型推导，那么你看到的就是⼀个右
值引⽤。
*/
void f(Widget&& param); //没有类型推导
//param是⼀个右值引⽤
Widget&& var1 = Widget(); //没有类型推导
//var1是⼀个右值引⽤
/*
因为通⽤引⽤是引⽤，所以他们必须被初始化。⼀个通⽤引⽤的初始值决定了它是代表了右值引⽤还是
左值引⽤。如果初始值是⼀个右值，那么通⽤引⽤就会是对应的右值引⽤，如果初始值是⼀个左值，那
么通⽤引⽤就会是⼀个左值引⽤。对那些是函数参数的通⽤引⽤来说，初始值在调⽤函数的时候被提
供：
*/
void t1(){
    template <typename T>
void f(T&& param); //param是⼀个通⽤引⽤
Widget w;
f(w); //传递给函数f⼀个左值;参数param的类型
//将会是Widget&,也即左值引⽤
f(std::move(w)); //传递给f⼀个右值;参数param的类型会是
//Widget&&,即右值引⽤
/*
对⼀个通⽤引⽤而⾔，类型推导是必要的,但是它还不够。声明引⽤的格式必须正确，并且这种格式是被
限制的。它必须是准确的T&&。再看看之前我们已经看过的代码⽰例:
*/
}
template<typename T>
void f(std::vector<T>&&param);
void t2(){
    std::vector<int> v;
    f(v);
}
int main(){
    t2();
}