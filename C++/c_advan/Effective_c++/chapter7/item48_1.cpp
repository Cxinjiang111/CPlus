#include<iostream>
using namespace std;
//递归 递归模板具现化
template<unsigned n>
struct Factorial{
    enum{value=n*Factorial<n-1>::value};
};
template<>
struct Factorial<0>
{
  enum{value=1};
};
int main()
{
    std::cout<<Factorial<10>::value;
}