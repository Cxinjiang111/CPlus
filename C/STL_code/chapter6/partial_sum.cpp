template<class InputIteator,class OutputIterator>
OutputIterator oprtial_sum(InputIteator first,InputIteator last,OutputIterator result)
{
    if(first==last) return result;
    *result=*first;
}
template<class InputIteator,class OutputIterator>
OutputIterator oprtial_sum(InputIteator first,InputIteator last,OutputIterator result)
{
   T value=*first;
   while(++first!=last)
   {
       value=value+first;
       *++result=value;
   }
    return ++result;
}

template<class InputIteator,class OutputIterator,class BinaryOperator>
OutputIterator oprtial_sum(InputIteator first,InputIteator last,OutputIterator result,BinaryOperator binary_op)
{
    if(first==last) return result;
    *result=*first;
}
template<class InputIteator,class OutputIterator,class BinaryOperator>
OutputIterator oprtial_sum(InputIteator first,InputIteator last,OutputIterator result,BinaryOperator binary_op)
{
   T value=*first;
   while(++first!=last)
   {
       value=binaary_op(value,*first);
       *++result=value;
   }
    return ++result;
}