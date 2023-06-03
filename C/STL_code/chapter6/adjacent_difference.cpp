//adjacent_difference 操作相邻两个内容之间的操作，默认是相减
//输入迭代器和输出迭代器
template<class InputIteator,class OutputIterator>
OutputIterator adjacent_difference(InputIteator first,InputIteator end,OutputIterator result)
{
    if(first==last) return result;
    *result=*first;
    iterator_traits<InputIteator>::value_type value=*first;
    return __adjacent_difference(first,last,result,value);//调用次函数
}
// 版本 1 
template<class InputIteator,class OutputIterator,class T>
OutputIterator __adjacent_difference(InputIteator first,InputIteator last,OutputIterator result,T *)
{
    T value =*first;
    // 结束条件
    while(++first!=last)
    {
        T tmp=*first;
        *++result=tmp-value;//前一个的插值向输出迭代器中保存，++result迭代器能够实现自增内存
        value=tmp;
    }
    result ++result;
}
/*
算法adjacen二中fference用来计算[first,las七）中相邻元素的差额。也就是说，它将＊丘rst赋值给＊result,并针对[first+l,last)内的每个迭代器i,将*i－*（i-1)之值赋值给*（result+(i-first))。
*/

//这个可以求相邻元素的任意简单操作 加入一个操作函数 binary_op
template<class InputIteator,class OutputIterator,class BinaryOperation>
OutputIterator adjacent_difference(InputIteator first,InputIteator end,OutputIterator result,BinaryOperation binary_op)
{
    if(first==last) return result;
    *result=*first;
    iterator_traits<InputIteator>::value_type value=*first;
    return __adjacent_difference(first,last,result,value_type(first),binary_op);
}
template<class InputIteator,class OutputIterator,class T>
OutputIterator __adjacent_difference(InputIteator first,InputIteator last,OutputIterator result,T ,class BinaryOperation)
{
    T value =*first;
    //
    while(++first!=last)
    {
        T tmp=*first;
        *++result=binary_op(tmp,value);
        value=tmp;
    }
    result ++result;

}
