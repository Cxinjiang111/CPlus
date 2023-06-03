#include "../inc/rightrf.h"
#include <utility>
#include <iostream>
using namespace std;
void right_references_1()
{
    int i = 42;
    //r 为i的引用，左值引用
    int &r = i;
    //rr 不可以引用左值i，
    //因为其是右值引用
    //int &&rr = i;
    //表达式是一个右值
    //不能用左值引用
    //int &r2 = i*42;
    //可以将const引用绑定到右值上
    const int &r3 = i * 42;
    //将rr2绑定到乘法结果上
    int &&rr2 = i * 42;
}

void right_references_2()
{
    //右值引用捕获字面常量值
    int &&rr1 = 42;
    //右值引用不能捕获左值
    //因为rr1为左值，下面操作非法
    //int &&rr2 = rr1;
}

void right_references()
{
    //右值引用捕获字面常量值
    int &&rr1 = 42;
    //通过move将左值转化为右值引用
    int &&rr3 = std::move(rr1);
}