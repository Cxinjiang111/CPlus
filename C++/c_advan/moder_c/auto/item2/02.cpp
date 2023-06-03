/*
Item1把模板类型推导分成三个部分来讨论ParamType在不同情况下的类型。在使⽤auto作为类型说明
符的变量声明中，类型说明符代替了ParamType，因此Item1描述的三个情景稍作修改就能适⽤于
auto：
类型说明符是⼀个指针(*)或引⽤(&)但不是通⽤引⽤(&&)
类型说明符⼀个通⽤引⽤
类型说明符既不是指针也不是引⽤
*/
#include<iostream>
using namespace std;
void somefun(int ,double){ //函数
    cout<<"soome fun who call me"<<endl;
}
void t1(){
    const char name[]="hello world";
    auto arr1=name;//arr1的类型是const char*
    auto &arr2=name;//arr2的类型是const char(&)[12]

    auto fun1=somefun; //fun1的类型是void (int,double)
    auto &fun2=somefun;//fun2的类型是void(&) (int,double)

}

int main(){
    t1();

    return 0;
}