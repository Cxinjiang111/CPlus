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



