#include<iostream>
using namespace std;
class Widget{
public:
    Widget()//构造函数
    {
        cout<<"构造函数"<<endl;
    }
    // Widget(const Widget &rhs)//拷贝构造函数
    // {
    //     cout<<"拷贝构造函数"<<endl;
    // }
    Widget& operator=(const Widget & rhs)//拷贝赋值
    {
        cout<<"拷贝赋值"<<endl;
        return *this;
    }
    Widget& operator()(const Widget & rhs)//拷贝函数赋值
    {
        cout<<"拷贝函数赋值"<<endl;
        return *this;
    }
    int a;  
};
/*
拷贝构造和拷贝赋值的区别 如果一个新对象被定义，
如果一个新对象被定义（例如以上语句中的w3)， 一定会有个构造函数被调用， 不可能调用赋值操作。 如果没有新对象被定义（例如前述的 “wl = w2'，语旬），就不会有构造函数被调 用， 那么当然就是赋值操作被调用。
opy构造函数是一个尤其重要的函数，因为它定义一个对象如何passedby value（值传递）
参数w是以byvalue方式传递给hasAcceptableQuality,所以在上述调用中 aWidget被复制到w体内。这个复制动作由阳dget的copy构造函数完成。 Pass-by-value意味“调用copy构造函数”。以byvalue传递用户自定义类型通常是个坏主意，Pass-by-reference-to-const往往是比较好的选择；详
*/
void dosomething(Widget w) //值传递
{
    cout<<w.a<<endl;
}
void dosomething1(Widget& w) //引用传递
{
    cout<<w.a<<endl;
}
int main2()
{
    Widget aw;

    cout<<"====="<<endl;
    aw.a=5;
    dosomething(aw);//output 拷贝构造函数 值传递回先生成一个对象
cout<<"====="<<endl;
    dosomething1(aw);//这个什么也不输出 没有发生拷贝构造也没有发生拷贝赋值 只是传递一个对象的指针，并没有生成额外的对象，这也就是常用引用传递而不用值传递的一部分原因，放置额外拷贝 
/*
构造函数
拷贝构造函数
0
=====
5

*/
    return 0;
}
int main()
{
    Widget aw;
    cout<<"====="<<endl;    
    Widget aw2=aw; //居然没有调用operator= 这个而是调用拷贝构造函数
    cout<<"====="<<endl;    
    Widget aw3(aw); //居然没有调用operator() 这个而是调用拷贝构造函数

/*
构造函数
=====
拷贝构造函数
=====
拷贝构造函数
*/
    return 0;
}