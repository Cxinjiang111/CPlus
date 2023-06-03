//偏特化
template<class T>
struct iterator_traits<const T*>
{
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
};
//全特化
template<class T>
struct iterator_traits
{
    typedef random_access_iterator_tag iterator_tag;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};
//消除由于继承带来的类型嵌套
template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type        difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference        reference;
};

//没有iterator_traits，如何制作iterator traits 

//两个iterator的值交换
template<class ForwardIterator1,class ForwardIterator2>
void iter_swap(ForwardIterator1 p,ForwardIterator2 q)
{
    //iterator_traits<ForwardIterator1>::value_type 寻找他的值的类型
    typename iterator_traits<ForwardIterator1>::value_type tmp=*p;
    *p=*q;
    *q=tmp;
}
//如果使用旧机制，就无法直接申明tmp，必须分两个函数来完成任务 这里使用时T的类型应该传什么呢？？
template<class ForwardIterator1,class ForwardIterator2,class T>
void iter_swap_impl(ForwardIterator1 p,ForwardIterator2 q,T*)
{
    T tmp=*p;
    *p=*q;
    *q=tmp;
}
template<class ForwardIterator1,class ForwardIterator2>
void iter_swap(ForwardIterator1 p,ForwardIterator2 q)
{
    iter_swap_impl<ForwardIterator1,ForwardIterator2>(p,q);//最后的一个类型不传，
}
/*
每个iterator type都必须提供这个三个函数，如果你要定义新的iterator，确保这三个函数都有新的定义的最简单方法，就是令你的iterator class继承之前的五个
base class之一，input_iterator,output_iterator,forward_iterator,bidrection_iterator,random_access_iterator
*/
