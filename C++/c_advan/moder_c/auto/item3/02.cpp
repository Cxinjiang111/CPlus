#include<iostream>
using namespace std;
// template<typename Container,typename Index>
// auto authAndAccess(Container &c,Index i)->decltype(c[i]){
//     authenticateUser();//异常捕获
//     return c[i];
// }
// /*
// 函数名称前⾯的auto不会做任何的类型推导⼯作。相反的，他只是暗⽰使⽤了C++11的尾置返回类型语
// 法，即在函数形参列表后⾯使⽤⼀个-> 符号指出函数的返回类型，尾置返回类型的好处是我们可以在函
// 数返回类型中使⽤函数参数相关的信息。在authAndAccess函数中，我们指定返回类型使⽤c和i。如果
// 我们按照传统语法把函数返回类型放在函数名称之前， c和i就未被声明所以不能使⽤。
// */
// //这里改动之后就把函数后的类型推导予以寄托到auto上，auto不在只是个摆设

// template<typename Container,typename Index>
// auto authAndAccess(Container &c,Index i){
//     authenticateUser();//异常捕获
//     return c[i];
// }
// /*
// 现在authAndAccess将会真正的返回c[i]的类型。现在事情解决了，⼀般情况下c[i]返回T& ，
// authAndAccess也会返回
// T&,特殊情况下c[i]返回⼀个对象，authAndAccess也会返回⼀个对象。
// */
// template<typename Container,typename Index>
// decltype(auto) authAndAccess(Container&c,Index i){
//     authenticateuser();
//     return c[i];
// }
//decltype(auto) 的使⽤不仅仅局限于函数返回类型
class Widget{

};
void t1(){
Widget w;
const Widget&cw=w;
Widget mywidget1=cw;//为什么这里不加const也能编译通过呢  一个非const接住const呢
//auto mywidget1=cw;
decltype(auto) mywidget2=cw;//const Widget&
}
int main(){
    t1();
    return 0;
}



