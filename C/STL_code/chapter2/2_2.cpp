#include<new>
//#include"jjalloc.h"
template<typename T1,typename T2>
inline void construct(T1*p1,const T2&value){
    new(p) T1(value);
    //p=new T1(value);
}
//C 语言和非数组申请C++的内存释放版本 只接受一个指针
template<class T>
inline void destory(T*pointer){
    pointer->~T();
}
//  这时第二个版本，接受两个迭代器，函数找出元素的数值型别 
template<class ForwardIterator>
inline void destory(ForwardIterator first,ForwardIterator last){
    __destory(first,last,value_type(first));//传入首尾迭代器
    //value_type(first)这里判断该型别的析构函数是否无关痛痒 ，若是 则什么也不用做，不用做不必要的释放 结束 
    //C++ 本身并不支持对指针所指之物的型别判断 
}
template<class ForwardIterator,class T>
inline void __destory(ForwardIterator first,ForwardIterator last,T*){
    typedef  typename __type_traits<T>::has_trivial_destructor trival_destructor;
    __destory__aux(first,last,trival_destructor());
}
template<class ForwardIterator>
inline void __destory__aux(ForwardIterator first,ForwardIterator last,__flase_type){
    for(;first<last;first++){
        destory(&*first);//遍历
    }
}
