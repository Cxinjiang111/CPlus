#include<iostream>
int f1(int)
{
    std::cout<<"f1 (int)"<<std::endl;
    return 0;
}
int f2(float)
{
  std::cout<<"f1 (int)"<<std::endl;
  return 0;
}
struct A{
    using fp1=int(*)(int);
    operator fp1(){return f1;} //重载函数指针 隐式转换
    using fp2=int(*)(float);
    operator fp2(){return f2;}
} a;
int main()
{
    int i=a(1);

    return 0;
}