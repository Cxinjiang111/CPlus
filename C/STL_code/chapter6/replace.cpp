template<class ForwardIterator,class T>
void  replace(ForwardIterator first,ForwardIterator last,const T& newvalue,const T&oldvalue)
{
    for(;first!=last;++first)
    {
        if(*first==oldvalue)
        {
            *first=newvalue;
        }
    }
    
}


