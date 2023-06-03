template<class InputIterator,class T>
T accmulate(InputIterator first,InputIterator last,T init)
{
    for(;first!=end;++first)
    {
        init+=*first;
    } 
    return init;
}

template<class InputIterator,class T,class BinaryOperator>
T accmulate(InputIterator first,InputIterator last,T init,BinaryOperator binary_op)
{
    for(;first!=end;++first)
    {
        init=binary_op(init,*first);
    } 
    return init;
}
/*

算法accumulate 用来计算init 和[first,last)内所有元素的总和，
你一定要提供一个初始值，因为当[first,last)为空区间时仍能获得一个明确定义的值

*/