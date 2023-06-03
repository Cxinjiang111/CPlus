#include<iostream>
using namespace std;
int callbackFun(int a,int b)
{
    cout<<"this is callbackFun"<<endl;
    return a+b;
}
typedef int (*FP)(int ,int);//定义一个函数指针类型
void callbackExec(FP fp,int m,int n)
{
    cout<<fp(m,n)<<endl;//调用指针函数fp
}
int main()
{

    callbackExec(callbackFun,5,6);//callbackFun 需传入一个指针 函数本身类型与数组，直接传入就行
    return 0;
}

