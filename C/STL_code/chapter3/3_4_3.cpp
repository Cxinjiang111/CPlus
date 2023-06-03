//P 90    value type
//型别之二：difference type
/*
difference type用来表示两个迭代器之间的距离，因此它也可以用来表示一个容器的最大容量，
因为对于连续空间的容器而言，头尾之间的距离就是其最大容量。 如果一个泛型算法提供计数功能，
例如STL的count(），其传回值就必须使用迭 代器的differencefype: 

*/
template<typename I,typename T>
//在自己定义类是需申明的型别，在此时编译器扮演者自动推导的作用
typename iterator_traits<T>::difference_type 
count(I first,I last,const T&value){
    typename iterator_traits<T>::difference_type n=0;
    for(;first!=last;++first){
        if(*first==value){
            ++n;
        }
    }
    return n;//n 就是两个迭代器之间的距离，这个n不一定是整数
}
//两种特化版本
template<typename I>
struct iterator_traits{
    typedef typename I::difference_type difference_type;
};
//为原生指针而设计的偏特化版
template<typename I>
struct iterator_traits<I*>{
    typedef ptrdiff_t difference_type;
};




