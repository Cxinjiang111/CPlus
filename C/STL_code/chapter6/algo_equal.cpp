template<class InputIterator1,class InputIterator2>
bool equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first)
{
    for(;first1!=last1;++first1,++first)
    {
        if(first1!=first)
        return false;
    }
    return true;
}
template<class InputIterator1,class InputIterator2,class BinaryOperator>
bool equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first,BinaryOperator binary_op)
{
    for(;first1!=last1;++first1,++first)
    {
       if(binary_op(first1,first))
        return false;
    }
    return true;
}

template<class InputIterator1,class T>
void fill(InputIterator1 first,InputIterator1 last,T value)
{
    for(;first!=last;++first)
    {
        *first=value;
    }
}
//这个对于N填充的数目没有边界检查
template<class InputIterator1,class N,class T>
void fill_n(InputIterator1 first,InputIterator1 last,N n,T value)
{
    
    while(n>0)
    {
        *++first=value;
        n--;
    }
    return first;
}

template<class ForwardIterator1,class ForwardIterator2>
void iter_swap(ForwardIterator1 a,ForwardIterator2 b)
{
    __iter_swap(a,b,value_type(a));
}