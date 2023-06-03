template<class ForwardIterator>
ForwardIterator adjcent_find(ForwardIterator first,ForwardIterator last)
{
    ForwardIterator next=first;
    while (first!=last)
    {
        ++first;
        if(*first==*next)
        return first;
        next=first;
    }
    return last;
}
template<class ForwardIterator,class BinaryPredicate>
ForwardIterator adjcent_find(ForwardIterator first,ForwardIterator last,BinaryPredicate binary_pred)
{
    ForwardIterator next=first;
    while (first!=last)
    {
        ++first;
        if(binary_pred(*first,*next))
        return first;
        next=first;
    }
    return last;
}









