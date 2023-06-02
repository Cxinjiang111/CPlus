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

void dosomething(Widget w) //值传递
{
    cout<<w.a<<endl;
}
void dosomething1(Widget& w) //引用传递
{
    cout<<w.a<<endl;
}

int main()
{
    Widget aw;
    cout<<"====="<<endl;    
    Widget aw2=aw; //居然没有调用operator= 这个而是调用拷贝构造函数
    cout<<"====="<<endl;    
    Widget aw3(aw); //居然没有调用operator() 这个而是调用拷贝构造函数
    cout<<"====="<<endl;
    aw.a=5;
    dosomething(aw);//output 拷贝构造函数 值传递回先生成一个对象
    cout<<"====="<<endl;
    dosomething1(aw);
/* 没有拷贝构造 系统还是回生成拷贝构造函数，35法则
构造函数
=====
=====
*/
    return 0;
}