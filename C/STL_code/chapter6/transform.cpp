template<class InputIterator,class OutputIterator,class UnaryOperation>
OutputIterator transform(InputIterator first,InputIterator last,OutputIterator result,UnaryOperation op)
{
    for(;first!=last;++first,++result)
    *result=op(first);
    return result;
}