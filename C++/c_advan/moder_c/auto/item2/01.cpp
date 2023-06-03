//Item 2:Understand auto type deduction 
/*
如果你已经读过Item1的模板类型推导，那么你⼏乎已经知道了auto类型推导的⼤部分内容，⾄于为什
么不是全部是因为这⾥有⼀个auto不同于模板类型推导的例外。但这怎么可能，模板类型推导包括模
板，函数，形参，但是auto不处理这些东西啊
你是对的，但没关系。auto类型推导和模板类型推导有⼀个直接的映射关系。它们之间可以通过⼀个⾮
常规范⾮常系统化的转换流程来转换彼此。
在f的调⽤中，编译器使⽤expr推导T和ParamType。当⼀个变量使⽤auto进⾏声明时，auto扮演了模板
的⻆⾊，变量的类型说明符扮演了ParamType的⻆⾊

template<typename T>
void f(ParamType param);
auto x=27;
const auto cx=x;
const auto &rx=cx;
*/
#include<iostream>
using namespace std;
template<typename T>
void func_for_x(T param){
    cout<<"func_for_x"<<endl;
}
template<typename T>
void func_for_cx(const T param){
// 理想化模板来推导rx的类型
    cout<<"func_for_cx"<<endl;
}
template<typename T>
void func_for_rx(const T& param){
    //理想化模板来推导rx的类型
   cout<<"func_for_rx"<<endl;
}
void t1(){
    auto x=27;
    const auto cx=x;
    const auto &rx=cx;
    //可以正确去类型推导
    func_for_x(x);
    func_for_x(cx);
    func_for_x(rx);
    //--------
    func_for_cx(x);
    func_for_cx(cx);
    func_for_cx(rx);
    //--------
    func_for_rx(x);
    func_for_rx(cx);
    func_for_rx(rx);
}
int main(){
    t1();
}
