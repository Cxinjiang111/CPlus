#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Widget{
public:
    Widget(){
        cout<<"Widget()"<<endl;
    }
    Widget(std::initializer_list<int>i1){
        cout<<"Widget(std::initializer_list<int>i1)"<<endl;
    }
    // Widget(int i,bool d);
    // Widget(int i,double d);

    // Widget(std::initializer_list<long double>i1);
    //Widget& opeartor float() const;
};
// Widget::Widget(int i,bool d)
// {
//     cout<<"Widget(int i,bool d)"<<endl;
// }
// Widget::Widget(int i,double d){
//     cout<<"Widget(int i,double d)"<<endl;
// }
// Widget::Widget(std::initializer_list<long double>i1){
//     cout<<"Widget(std::initializer_list<long double>i1)"<<endl;
// }
int main(){
//编译器热衷于把括号初始化与使std::initializer_list构造函数匹配了，热衷程度甚⾄超过了最佳匹配
  //  Widget w{10,5.0};//这里使用的是花括号，而使用括号时就会匹配括号的构造函数
    //output    Widget(std::initializer_list<long double>i1) 优先调用初始化列表
    //只有当没办法把括号初始化中实参的类型转化为std::initializer_list时，编译器才会回到正常的函数决议流程中。 
//这⾥，编译器会直接忽略前⾯两个构造函数，然后尝试调⽤第三个构造函数，也即是std::initializer_list构造函数。
//调⽤这个函数将会把int(10)和double(5.0)`转换为bool，由于括号初始化拒绝变窄转换，所以这个调⽤⽆效，代码⽆法通过编译。
//但是这个代码并没有报错


//Widget w1;//output    Widget()
//Widget w2{};//output  Widget()

//Widget w3();//error 不允许这样 note: remove parentheses to default-initialize a variable

Widget w4({});
Widget w5{{}};//{}这个符号就几乎标记着我要优先调用初始化列表 如果没有匹配的初始化列表 那就只能去匹配括号
return 0;

}