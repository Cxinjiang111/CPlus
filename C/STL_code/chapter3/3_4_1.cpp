//迭代器所指对象的型别，称为该迭代器的value type 
//如果传入的是函数返回值，编译器就不能识别了
//此时采用内嵌型别就是个好主意
#include<iostream>

template<typename T>
struct MyIter{
    typedef T value_type;
    T *ptr;
    MyIter(T*p=0):ptr(p){}
    T&operator*()const{return *ptr;}
};
template<class I>
typename I::value_type  //这一整行是func的返回值型别。
func(I ite){
    return *ite;
}
//错误的示范
// template<class I>
// //typename I::value_type  
// I* func(I ite){
//     return &ite;
// }

int main(){
    MyIter<int> ite(new int(8));
    std::cout<<func(ite);
    
}
/*
注意， func()的回返型别必须加上关键词七ypenarne, 因为T是一个
template参数， 在它被编译器具现化之前， 编译器对T一无所悉， 
换句话说， 编译器此时并不知道Myiter<T>: : value_type代表的是一个型别或是个memberfunction或是一个data member。 
关键词typenarne的用意在于告诉编译器这是 个型别，
如此才能顺利通过编译。
*/