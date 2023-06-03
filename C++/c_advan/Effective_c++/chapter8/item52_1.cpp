#include<iostream>
#include<iostream>
using namespace std;
class StandardNewDeleteForms{
public:
    //正常的new delete  
    static void*operator new(std::size_t size)throw(){
        return ::operator new(size);
    }
    static void operator delete(void*pMemory)throw()
    {
        ::operator delete(pMemory);
    }
    //placement new/delete
    static void *operator new(std::size_t size,void*ptr)throw()
    {
            return ::operator new(size,ptr);
    }
    static void operator delete(void*pMemory,void *ptr)throw()
    {
        return ::operator delete(pMemory,ptr);
    }
    //placement new/delete
    static void *operator new(std::size_t size,void*ptr)
    {
            return ::operator new(size,ptr);
    }
    static void operator delete(void*pMemory)
    {
        return ::operator delete(pMemory);
    }
};
int main()
{

}




