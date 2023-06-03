#include<iostream>
#include<iterator>
#include<string.h>
#include<stdio.h>
using namespace std;
template<class InputIterator,class OutputIterator>
inline OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result)
{
    return __copy_dispatch<InputIterator,OutputIterator>()(first,last,result);//提供一层间接性
}
//特殊版本1 重载版本
inline char*copy(const char*first,const char*last,char*result)
{
//void *memmove (void *__dest, const void *__src, size_t __n)
        memmove(result,first,last-first);//
        return result+(last-first);
}
//完全泛化版本
template<class InputIterator,class OutputIterator>
struct __copy_dispatch{
    OutputIterator operator()(InputIterator first,InputIterator last,OutputIterator result){
        return __copy(first,last,__iterator_category(first));//__iterator_category(first) 这里提供一种类型识别，一边在下面可以根据类型选择不同的版本
    }
};
//偏特化版本1 两个参数都是T*指针形式
template<class T>
struct __copy_dispatch<T*,T*>
{
    T*operator()(T*first,T*last,T*result){
        typedef typename __type_traits<T>::has_trivial_assignment_operator t;
        return __copy_t(first,last,result,t());
    }
};
//偏特化版本1 ，第一个参数为const T*指针形式，第二个参数都是T*指针形式 
//                 比如输入迭代器            输出迭代器
template<class T>
struct __copy_dispatch<const T*,T*>
{
    T*operator()(const T* first,const T*last,T*result)
    {
        typedef typename __type_traits<T>::has_trivial_assignment_operator t;
        return __copy_t(first,last,result,t());
    }    
};
template<class InputIterator,class OutpurIterator>
inline OutpurIterator __copy(InputIterator first,InputIterator last,OutpurIterator result,InputIterator tasd)

