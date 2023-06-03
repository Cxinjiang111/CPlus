#include<iostream>
using namespace std;
void callbackFun()
{
    cout<<"this is callbackFun"<<endl;
}
typedef void (*FP)();
void callbackExec(FP fp)
{
    return fp();//不带参数的函数
}
int main()
{

    callbackExec(callbackFun);
    return 0;
}

