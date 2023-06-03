/*
已字典排列方式对两个序列[first1, last1)和[first2,last2)比较，
比较操作针对两序列中对应位置上的元素进行，并持续到某一组中对应元素彼此不相等，
同时到达last1 last2 
到达last1 或者last2
当这个函数在对应位置上发现第一组不相等的元素时，有以下可能
如果第一序列的元素较小，返回true，否则返回false
如果达到last1 而尚未到达last2，返回true
如果达到last2 而尚未达到last1  返回true
如果同时到达last1 和last2 返回false

*/
#include<iostream>
template<class InputIterator1,class InputIterator2>
bool lexicographcal_compare(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,InputIterator2 last2)
{
    for(;first1!=last1&&first2!=last2;++first1,++first2)
    {
        if(*first1<*first2)
        {
            return true;
        }
        else if(*first1<*first2)
        {
            return false;
        }
        return first1==last1&&first2!=last2;
    }
}
/*
mismatch
用来平行比较两个序列，之处两者之间的第一个不匹配点，返回一堆迭代器，分别指向两序列中的不匹配点，

*/
template<class InputIterator1,class InputIterator2>
std::pair<InputIterator1,InputIterator2> mismatch(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2)
{
while(first1!=last1;++first1,++first2)
{
    if(*first1!=*first2)
    break;
}
return _pair<InputIterator1,InputIterator2>(first1,first2)
}
template<class InputIterator1,class InputIterator2>
bool lexicongraphical_compare(InputIterator1 first1,InputIterator1 end1,InputIterator2 first2,InputIterator2 end2){
    for(;first1!=end1&&first2!=end2;++first1,++first2)
    {
        if(*first1<*first2)
        {
            return true;
        }
        if(*first1>*first2){
            return false;
        }
    }
    return first1==end1&&first2!=end2;
}
template<class InputIterator1,class InputIterator2,class BinaryOp>
bool lexicongraphical_compare(InputIterator1 first1,InputIterator1 end1,InputIterator2 first2,InputIterator2 end2,BinaryOp,op){
    for(;first1!=end1&&first2!=end2;++first1,++first2)
    {
        if(op(*first1,*first2))
        {
            return true;
        }
        if(op(*first2,*first1)){
            return false;
        }
    }
    return first1==end1&&first2!=end2;
}

