#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Widget{
public:
    Widget(int i,bool d);
    Widget(int i,double d);
    Widget(std::initializer_list<long double>i1);
    vector<int> a{1,4,6};
    int y=0;
    //string s("hello");即使有构造函数也不行

    //int z(0); error
};
Widget::Widget(int i,bool d)
{
    cout<<"Widget(int i,bool d)"<<endl;
}
Widget::Widget(int i,double d){
    cout<<"Widget(int i,double d)"<<endl;
}
Widget::Widget(std::initializer_list<long double>i1){
    cout<<"Widget(std::initializer_list<long double>i1)"<<endl;
}
void t1(){
   vector<int> a{1,4,6,2};//初始化
    vector<int> a1{0};
    vector<int> a2(0);//调用构造函数中的一种
    //vector<int> a3=0; //错误，左右类型不匹配。
    /*
括号表达式有⼀个异常的特性，它不允许内置类型隐式的变窄转换（narrowing conversion）。如果⼀
个使⽤了括号初始化的表达式的值⽆法⽤于初始化某个类型的对象，代码就不会通过编译：
    */
//    double x,y,z;
//    int sum{x+y+z};
//    int x,y,z;
//    double sum{x+y+z};
//使⽤小括号和"="的初始化不检查是否转换为变窄转换，因为由于历史遗留问题它们必须要兼容⽼旧代码

Widget w1(10, true); // 调⽤构造函数
cout<<"====================="<<endl;
Widget w2{10, true}; // 同上
cout<<"====================="<<endl;
Widget w3(10, 5.0); // 调⽤第⼆个构造函数
cout<<"====================="<<endl;
Widget w4{10, 5.0}; // 同上
/* 为何第二个会自己调用初始化列表呢
Widget(int i,bool d)
=====================
Widget(std::initializer_list<long double>i1)
=====================
Widget(int i,double d)
=====================
Widget(std::initializer_list<long double>i1)
*/
}


int main(){
    return 0;
}