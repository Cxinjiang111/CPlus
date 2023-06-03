template<class ForwardIterator,class Generator>
void generate(ForwardIterator first,ForwardIterator last,Generator f)
{
    for(;first!=last;++first)
    {
        *first=f();
    }
}












