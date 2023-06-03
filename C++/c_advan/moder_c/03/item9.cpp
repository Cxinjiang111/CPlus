#include<iostream>
using namespace std;
//二者等价
typedef void (*FP)(int a,int b);//那么FP就相当于一种类型别名，

using FP=void (*)(int a,int b); 
//当然，两个结构都不是⾮常让⼈满意，没有⼈喜欢花⼤量的时间处理函数指针类型的别名[0]，所以⾄少
//在这⾥，没有⼀个吸引⼈的理由让你觉得别名声明⽐typedef好。
int main(){
    FP f1;


    return 0;
}