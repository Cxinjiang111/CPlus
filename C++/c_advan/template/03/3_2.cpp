#include<iostream>
//Difference type
template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::value_type value_type;//消除嵌套类型
    typedef typename Iterator::difference_type difference_type;
};
template<class T>
class B{
public:
    typedef T value_type;
    typedef const T* const_value_type;
    typedef size_t difference_type;
    T val;
};
template<class Base>
class D{
public:
    typedef iterator_traits<Base> value_type;
};
template<class InputItertor ,class T>
typename iterator_traits<InputItertor>::difference_type 
count(InputItertor first,InputItertor last,const  T&x)
{
    typename iterator_traits<InputItertor>::difference_type  n=0;
    while (first!=last)
    {
        if(*first==x)
            n++;
        first++;
    }
    return n;
}
int main()
{
    size_t s=56;
    D<B<int>>::value_type::difference_type a=s;
    std::cout<<a<<std::endl;
}