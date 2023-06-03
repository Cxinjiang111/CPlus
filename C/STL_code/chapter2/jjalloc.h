//设计一个简单的空间配置器 
#pragma once
#include<new>
#include<cstddef>
#include<climits>
#include<cstdlib>
#include<iostream>
#include<error.h>

namespace JJ{
    template<class T>
    //
    inline T* _allocate(ptrdiff_t size,T*){
        std::set_new_handler(nullptr);
        //::前面什么都不加 脱离本层命名空间 进入上一层命名空间
        T*tmp=(T*)(::operator new((size_t(size*sizeof(T)))));
        if(tmp==0){
            std::cerr<<"out of memory";
            exit(1);
        }else{
            std::cout<<"get memory success";
        }
        return tmp;
    }
    template<class T>
    inline void _deallocate(T*buffer){
        ::operator delete(buffer);
    }
    template<class T1,class T2>
    //构造函数  
    inline void _construct(T1*p,const T2&value){
        new(p) T1(value);
    }
    template<class T>
    inline void _destory(T*ptr){
        ptr->~T();
    }
    template<class T>
    class allocator{
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;//大小
        template<class U>
        struct rebind{
            typedef allocator<U> other;
        };
        //这里不好理解         //内存配置操作
        pointer allocate(size_type n,const void *hint=0){   //1
            std::cout<<"allocator ::allocate"<<std::endl;
            return _allocate((difference_type)n,(pointer)0);
        }
        //内存释放
        void deallocate(pointer p,size_type n){  //  3
            std::cout<<"allocator ::deallocate"<<std::endl;
            _deallocate(p);
        }
        //负责对象构造
        void construct(pointer p,const T&value){  // 2
            std::cout<<"allocator ::construct"<<std::endl;
            _construct(p,value);
        }
        //对象析构
        void destory(pointer p){
            std::cout<<"allocator ::destory"<<std::endl;
            _destory(p);}
        //
        pointer address(reference x){return (pointer)&x;}

        const_pointer const_address(const_reference x){
            return (const_pointer)&x;}

        size_type max_size()const{ return size_type(UINT_MAX/sizeof(T));}
    };


}




