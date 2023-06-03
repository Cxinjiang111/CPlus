#include<iostream>
#include<iterator>
//iterator_traits 定义的数个型别，
template<class InputItetator,class Distance>
void advance_II(InputItetator&i,Distance n)
{
    for(;n>0;--n,++i)
    {

    }
}
template<class InputItetator,class Distance>
void advance_BI(InputItetator&i,Distance n)
{
    if(n>=0)
    {
        for(;n>0;--n,++i){}
    }
    else{
        for(;n<0;++n,--i){}
    }
}
template<class RandomAccessIterator,class Distance>
void advance_RAI(RandomAccessIterator&i,Distance n)
{
    i+=n;
}
//在面对想要根据不同的迭代器来选择不同的advance 时 ，我会这么写 
template<class InputIterator,class Distance>
void advace(InputIterator &i,Distance n)
{
    if(is_random_access_iterator(i))
    {
        advance_RAI(i,n);
    }
    else if(is_bidirectional_iterator(i))
    {
        advance_BI(i,n);
    }
    else{
        advance_II(i,n);
    }
}
//上述方法很慢 ，我们应该想到函数重载开达到区分函数的功能。这里我们对concepts进行重载，而不是type进行重载
//但C++并不支持concepts重载，所以找出一种以C++性别系统来表示  就能模拟concepts的函数重载效果
/*
第一步为每一个iterator concepts定义一个专属型别，作为tag之用，我们不在乎这些型别实际是什么，只要独一无二就行
第二部是将三个advance版本进行重载 以上述所谓的标签型别作为重载识别
*/

template<class InputItetator,class Distance>
void advance_II(InputItetator&i,Distance n，ipu)
{
    for(;n>0;--n,++i)
    {

    }
}
template<class InputItetator,class Distance>
void advance_BI(InputItetator&i,Distance n)
{
    if(n>=0)
    {
        for(;n>0;--n,++i){}
    }
    else{
        for(;n<0;++n,--i){}
    }
}
template<class RandomAccessIterator,class Distance>
void advance_RAI(RandomAccessIterator&i,Distance n)
{
    i+=n;
}
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_access_iterator_tag:public bidirectional_iterator_tag{};
template<class InputIterator,class Distance>
void advace(InputIterator &i,Distance n,input_iterator_tag) //input_iterator_tag 这个仅仅作为标签，识别凭证而已 实现重载
{
    for(;n>0;--n,++i)
    {

    }
}
template<class InputIterator,class Distance>
void advace(InputIterator &i,Distance n,bidirectional_iterator_tag)
{
    if(n>=0)
    {
        for(;n>0;--n,++i){}
    }
    else{
        for(;n<0;++n,--i){}
    }
}
template<class InputIterator,class Distance>
void advace(InputIterator &i,Distance n,random_access_iterator_tag)
{
    i+=n;
}

class B{
public:
    typedef int value_type;
    typedef const int* const_value_type;
    
    int val;
};