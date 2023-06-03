/*
算术类仿函数
加法，减法，乘法，除法，取模，去反。

*/
#include<iostream>
#include<functional>
using namespace std;
template <class _Arg1, class _Arg2, class _Result>
struct _binary_function {
  typedef _Arg1 first_argument_type;
  typedef _Arg2 second_argument_type;
  typedef _Result result_type;
};      

template <class _Tp>
struct _plus : public _binary_function<_Tp,_Tp,_Tp> {
  _Tp operator()(const _Tp& __x, const _Tp& __y) const { return __x + __y; }
};

int main(){
    _plus<int> objplus;
   cout<<objplus(1,2)<<endl;

    return 0;
}

