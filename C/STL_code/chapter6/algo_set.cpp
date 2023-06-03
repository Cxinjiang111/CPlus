template<class InputIterator1,class InputIterator2,class OutputIterator>
OutputIterator set_union(InputIterator1 first1,InputIterator1 last1,
                        InputIterator2 first2,InputIterator2 last2
                        ,OutputIterator result)
{
    while(first1!=last1&&first2!=last2)
    {
        if(*first1<*first2)
        {
            *result=*first1;
            ++first1;
        } 
        else if (*first1>*first2)
        {
            *result=*first2;
            ++first2;
        }
        else{
             *result=*first2;
             ++first1;
             ++first2;
        }
        ++result;
    }
}

template<class InputIterator1,class InputIterator2,class OutputIterator>
OutputIterator set_differen(InputIterator1 first1,InputIterator1 last1,
                        InputIterator2 first2,InputIterator2 last2
                        ,OutputIterator result)
{
    while(first1!=last1&&first2!=last2)
    {
        if(*first1<*first2)
        {
            *result=*first1;
            ++first1;
            ++result;
        } 
        else if (*first2<*first1)
        {
            ++first2;
        }
        else{
             ++first1;
             ++first2;
        }

    }
}

