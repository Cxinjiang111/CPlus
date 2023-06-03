#include<iostream>
template<class I,class T>
void f_impl(I iter,T t)
{
    T tmp;
}
template<class T>
inline void f(T iter) 
{
    
    f_impl(iter,*iter);
}
struct Node{
    int val;
    Node *next;
};
//全特化
template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::value_type value_type;//消除嵌套类型
};
//上述的T是个node_warp 想要拿到value_type则是嵌套型别
//偏特化，我们需要针对每一种指针型别做出另一种定义
// template<class T>
// struct iterator_traits<T*>
// {
//     typedef T value_type;//这个value_type 是T* 的吗？
// };
// //const iterator *
// template<class T>
// struct iterator_traits<const T*>
// {
//     typedef T value_type;//这个T是const T*吗?
// };



// template<class Node>
// struct node_wrap
// {
//     //typedef Node value_type;
//     typename iterator_traits<Node>::value_type;//这样可以消除 全特化、

//     Node*ptr;
// }; 
template<class InputIterator>
typename iterator_traits<InputIterator>::value_type 
sum_nonempty(InputIterator first,InputIterator last)
{
    typename iterator_traits<InputIterator>::value_type result=*first++;
    for(;first!=last;++first)
    {
        result+=*first;
    }
    return result;
}
template<class T>
class B{
public:
    typedef T value_type;
    typedef const T* const_value_type;
    T val;
};
template<class Base>
class D{
public:
    typedef iterator_traits<Base> value_type;
};
int main()
{
    int c=5;
    
    D<B<int>>::value_type::value_type a=c;
    //D<B<int>>::value_type 第一层嵌套得到iterator_traits<Base> 的类型
    //D<B<int>>::value_type::value_type 得到int的类型 这就是解决嵌套类型的问题  
    std::cout<<a<<std::endl;
    return 0;
}



