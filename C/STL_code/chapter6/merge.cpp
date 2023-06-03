template<class InputIterator1,class InputIterator2,class OutputIterator>
OutputIterator merge(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,InputIterator2 last2,OutputIterator result)
{
    while (first1!=last1&&first2!=last2)
    {
        if(first1<first2)
        {
            ++first1;
            *result=*first1;
        }
        else{
            ++first2;
            *result=*first2;
        }
        ++result;
    }
    return copy(first2,last2,copy(first1,last1));
}
