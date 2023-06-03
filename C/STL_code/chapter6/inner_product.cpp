template<class InputIterator1,class InputIterator2,class T>
//两向量之间的内积和
T inner_product(InputIterator1 first1,InputIterator1 last,InputIterator2 first2,T init)
{
    for(;first1!=last;++first1,++first2)
    {
        init=init+(*first1* *first2)
    }
    return init;
}
//这样就可以实现任意组合操作了
template<class InputIterator1,class InputIterator2,class T,class BinaryOperation1,class BinaryOperation2>
//两向量之间的内积和
T inner_product(InputIterator1 first1,InputIterator1 last,InputIterator2 first2,T init,BinaryOperation1 binary_op1,BinaryOperation2 binary_op2)
{
    for(;first1!=last;++first1,++first2)
    {
        init=binary_op1(init,binary_op2(*first1,first2));//先是binary_op2对迭代器的数据进行操作，然后在进行binary_op1的操作。
    }
    return init;
}

