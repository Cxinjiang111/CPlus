#include<new>
#include<iostream>
#include<cassert>
void noMoreMemory()
{
    std::cerr<<"out of memory";
    abort();
}
typedef void(*new_handler)();
new_handler set_new_handler(new_handler p)throw();
void test()
{
    set_new_handler(noMoreMemory);
    /*
    int* p = new int[100000000000000];   //well, so BIG!
    assert(p);

    p = new int[100000000000000000000];  //[Warning] integer constant is too large for its type
    assert(p);
    */

}
class Foo{
public:
    long _x;
public:
    Foo(long x=0):_x(x){}
//“= default”只能出现在默认构造函数、复制/移动构造函数、复制/移动赋值运算符和析构函数中
    //不能使用default自动会生成的
    //void *operator new(size_t size)=default;
    //void operator delete(void*p ,size_t size)=default;
    void *operator new[](size_t size)=delete;
    void operator delete[](void *p,size_t size)=delete;
};
int main()
{
    Foo *p1=new Foo(5);
    delete p1;
    // Foo*p2=new Foo[10];//明确的报错
    // delete[]p2;

}

