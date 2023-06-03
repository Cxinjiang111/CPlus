 void operator delete(void *rawMemory)throw()
 {
     if(rawMemory==0)//如果将被删除的是个null指针 什么也不做
        return ;

    //归还所指内存
 }

#include<new>

class Base{
public:
    static void*operator new(std::size_t size)throw(std::bad_alloc);
    static void operator delete(void*rawMemory,std::size_t size)throw();
    ~Base();
};
class Derived:public Base{//这里继承了operator new

};
void operator delete(void *rawMemory,std::size_t size)throw()
{
     if(rawMemory==0)//如果将被删除的是个null指针 什么也不做
        return ;

    if(size!=sizeof(Base))
    {
        ::operator delete(rawMemory);
        return ;
    }
 }