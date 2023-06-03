//更一般的函数对象，Y=f(X)
//这里可以返回任何值，因为result完成了转化结果的存储，
template<class InputIterator,class OutputIteator,class UnaryFunction>
OutputIteator transform(InputIterator first,InputIterator last,OutputIteator result,UnaryFunction f)
{
    while (first!=last)
    {
        *result++=f(*first++);

    }
    return result;
    
}