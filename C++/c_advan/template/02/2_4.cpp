//替代需要我们向前遍历时并可能修改迭代器的值，前向迭代器有读性，输出迭代器可写性
template<class ForwardIterator,class T>
void replace(ForwardIterator first,ForwardIterator last,
            const T&old_value,const T&new_value)
{
    for(;first!=last;++first)
    {
        if(*first==old_value)
            *first=new_value;
    }
}
//adjacent_find只做只读动作，
template<class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first,ForwardIterator last)
{   
    if(first==last)
        return first;
    ForwardIterator next=first;
    while(++next!=last)
    {
        if(*next==*first)
            return first;
        first=next;
    }
    
}