#include<iostream>
#include<deque>
using namespace std;
/*
容器通过传引⽤的⽅式传递⾮常量左值引⽤，因为返回⼀个引⽤允许⽤⼾可以修改容器。但是这意味着
在这个函数⾥⾯不能传值调⽤，右值不能被绑定到左值引⽤上（除⾮这个左值引⽤是⼀个const，但是这
⾥明显不是）。
公认的向authAndAccess传递⼀个右值是⼀个edge case。⼀个右值容器，是⼀个临时对象，通常会在
authAndAccess调⽤结束被销毁，这意味着authAndAccess返回的引⽤将会成为⼀个悬置的(dangle)引
⽤。但是使⽤向authAndAccess传递⼀个临时变量也并不是没有意义，有时候⽤⼾可能只是想简单的获
得临时容器中的⼀个元素的拷⻉，⽐如这样：
*/\
deque<string> makeStringDeque();
auto s=autoAndAccess(makeStringDeque(),3);
/*
要想⽀持这样使⽤authAndAccess我们就得修改⼀下当前的声明使得它⽀持左值和右值。重载是⼀个不
错的选择（⼀个函数重载声明为左值引⽤，另⼀个声明为右值引⽤），但是我们就不得不维护两个重载
函数。另⼀个⽅法是使authAndAccess的引⽤可以绑定左值和右值，Item24解释了那正是通⽤引⽤能做
的，所以我们这⾥可以使⽤通⽤引⽤进⾏声明：

*/
template<typename Container,typename Index>
decltype(auto) authAndAccess(Container&&c,Index i);
/*
在这个模板中，我们不知道我们操纵的容器的类型是什么，那意味着我们相当于忽略了索引对象的可
能，对⼀个未知类型的对象使⽤传值是通常对程序的性能有极⼤的影响在这个例⼦中还会造成不必要的
拷⻉，还会造成对象切⽚⾏为，以及给同事落下笑柄。但是就容器索引来说，我们遵照标准模板库对于
对于索引的处理是有理由的，所以我们坚持传值调⽤。

*/
//C++14 版本
template<typename Container,typename Index>
decltype(auto) authAndAccess(Container&&c,Index i){
    authenticateUser();
    return std::forward<Container>(c)[i];
}
//C++11版本
template<typename Container,typename Index> //最终的C++11版本
auto authAndAccess(Container&& c,Index i)
->decltype(std::forward<Container>(c)[i])
{
    //std::forward<Container>(c)[i] 
    authenticateUser();
    return std::forward<Container>(c)[i];
}
/*
对⼀个名字使⽤decltype将会产⽣这个名字被声明的类型。名字是左值表达式，但那不影响decltype的
⾏为，decltype确保产⽣的类型总是左值引⽤。换句话说，如果⼀个左值表达式除了名字外还有类型，
那么decltype将会产⽣T&LEIX .这⼏乎没有什么太⼤影响，因为⼤多数左值表达式的类型天⽣具备⼀个
左值引⽤修饰符。
*/
int x=0;
decltype(auto) f1(){ //-->int
    int x=0;
    return x;//decltype(x）是int，所以f1返回int
}
decltype(auto) f2(){   //--->int&
    int x=01;
    return (x);//decltype((x))是int&，所以f2返回int&
}


