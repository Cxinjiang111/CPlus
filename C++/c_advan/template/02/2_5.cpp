
/*如果说前向迭代器时单项链表，那么BidirectionalIterator则是双向链表*/
template<class BidirectionalIterator,class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first,BidirectionalIterator last,OutputIterator result)
{
    while(first!=last)
    {
        --last;
        *result=*last;
        result++;
    }
    return result;
}
template<class BidirectionalIterator,class OutputIterator>
OutputIterator copy(BidirectionalIterator first,BidirectionalIterator last,OutputIterator result)
{
    while(first!=last)
    {     
        *result=*first;
        result++;
        first++;
    }
    return result;
}