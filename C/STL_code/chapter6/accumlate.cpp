#include<numeric>
#include<iostream>
//accumlate
//版本1
template<class InputIterator,class T>
T &accumlate(InputIterator first,InputIterator end,T init)
{
    for(;first!=last ,++first)
    {
        init+=*first;
    }
    return init;
}
//版本2 可以自定义操作函数
template<class InputIterator,class T,class BinaryOperation>
T &accumlate(InputIterator first,InputIterator end,T init,BinaryOperation f)
{
    for(;first!=last ,++first)
    {
        init=f(init,*first);
    }
    return init;
}
