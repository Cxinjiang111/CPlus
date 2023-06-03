//3.4.4 迭代器相应型别之四： pointer type 
/*pointers和references在C+＋中有非常密切的关联。 如果”传回一个左值，
令它代表p所指之物”是可能的，那么“传回一个左值，令它代表p所指之物的地址”也一定可以。
也就是说，我们能够传回一个pointer,指向迭代器所指之物。
*/
Item&operator*()const {return *ptr;}//reference type
Item*operator->()const{return ptr;}//pointer type

template<typename I>
struct iterator_traits{
    typedef typename I::pointer;
    typedef typename I::reference;
};
//特化版本<T*>已经限制了传入的值的类型
template<typename T>
struct iterator_traits<T*>{
    typedef T*pointer;
    typedef T& reference;
};
//特化版本<T*>已经限制了传入的值的类型
template<typename T>
struct iterator_traits<const T*>{
    typedef const T*pointer;
    typedef const T& reference;
};