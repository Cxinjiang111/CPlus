/*
作为分配器作用的第二个例子，假设你有两个堆，命名为Heap1和Heap2类。每个堆类有用于进行分配和回收
的静态成员函数：
*/
#include<iostream>
#include<vector>
#include<set>
#include<list>
#include<map>
using namespace std;
/*
更进一步认为你想在不同的堆里联合定位一些STL容器的内容。同样没有问题。首先，你设计一个分配器，
使用像Heap1和Heap2那样用于真实内存管理的类：???
*/

class size_type{

};
class Widget{

};
class Heap1{
public:
    static void*alloc(size_t numBytes,const void*memoryBlockToBeNear);
    static void delloc(void *ptr);
};
class Heap2{
public:
    static void*alloc(size_t numBytes,const void*memoryBlockToBeNear);
    static void delloc(void *ptr);
};
template<typename T,typename Heap>
class SpecificHeapAllocator{
public:
    typedef T* pointer;

    pointer allocate(size_type numObject,const void*localityHint=0)
    {
        return static_cast<pointer>(Heap::alloc((sizeof(T)*numObject),localityHin));
    }

    void dellocate(pointer ptrToMemory,size_type numObjects)
    {
        Heap::delloc(ptrToMemory);
    }
};
int main()
{
    Heap1 h1;
    SpecificHeapAllocator<int,Heap1> v;
    SpecificHeapAllocator<int,Heap2> v;

    vector<int,SpecificHeapAllocator<int,Heap1> >v;
    set<int,SpecificHeapAllocator<int,Heap1> >s;

    list<Widget,SpecificHeapAllocator<Widget,Heap2> >L;

    map<int,string,less<int>,SpecificHeapAllocator<pair<const int,string>,Heap2> >m;//?????
}

/*
在这个例子里，很重要的一点是Heap1和Heap2是类型而不是对象。STL为用不同的分配器对象初始化相同类
型的不同STL容器提供了语法，但是我将不让你看它是什么。那是因为如果Heap1和Heap2是对象而不是类
型，那么它们将是不等价的分配器，那就违反了分配器的等价约束，在条款10有详细说明。
*/

