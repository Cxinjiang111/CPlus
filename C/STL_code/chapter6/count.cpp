#include<iterator>
#include<iostream>
#include<type_traits>
template<class ForwardIterator,class T>
typename iterator_traits<ForwardIterator>::difference_type count(ForwardIterator first,ForwardIterator last,const T &value)
{
    typename iterator_traits<ForwardIterator>::dirrference_type n=0;
    while (first!=last)
    {
        if(*first!=value)
        {
            count++;
        }
        ++first;
    }
    return n;
}
template<class ForwardIterator,class BinaryPredicate>
typename iterator_traits<ForwardIterator>::difference_type count_if(ForwardIterator first,ForwardIterator last, BinaryPredicate pred)
{
    typename iterator_traits<ForwardIterator>::dirrference_type n=0;
    while (first!=last)
    {
        if(pred(*first))
        {
            count++;
        }
        ++first;
    }
    return n;
}