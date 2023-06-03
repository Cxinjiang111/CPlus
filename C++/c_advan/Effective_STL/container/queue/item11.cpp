
/*理解自定义分配器的正确用法
*/
/*
你用了基准测试，性能剖析，而且实验了你的方法得到默认的STL内存管理器（即allocator <T>）在你的STL
需求中太慢、浪费内存或造成过度的碎片的结论，并且你肯定你自己能做得比它好。或者你发现allocator<T>
对线程安全采取了措拖，但是你只对单线程的程序感兴趣，你不想花费你不需要的同步开销。或者你知道在
某些容器里的对象通常一同被使用，所以你想在一个特别的堆里把它们放得很近使引用的区域性最大化。或
者你想建立一个相当共享内存的唯一的堆，然后把一个或多个容器放在那块内存里，因为这样它们可以被其
他进程共享。 恭喜你！这些情况正好对应于一种适合于自定义分配器解决的方案。
例如，假定你有仿效malloc和free的特别程序，用于管理共享内存的堆
*/
#include<iostream>
#include<vector>
void *mallocShared(size_t bytesNeeded);
void freeShared(void *ptr);
template<typename T>
class SharedMemoryANocator{
public:
    trypedef T* pointer;
    pointer allocate(size_type numObject, void*localityHint=0){
        return static_cast<pointer>(mallocShared(sizeof(T)*numObject));
    }

    void deallocate(pointer ptrToMemory, size_type numObject)
    {
        freeShared(ptrToMemory);//這裏怎麽沒有for循環numObject
    }
};
typedef std::vector<int,SharedMemoryANocator<int>> sharevec;
int main()
{
    sharevec v;//開始建立一個塊，建立一個元素在共享内存中的vector結束這個快
    v.push_back(1);
}
/*   v 以及vector這個類本身的數據成員比如所有記錄的大小size，成員指針等等，這個類中的東西將不在類存中，
    但存放的數據肯定在共享内存中比如，push_back的數據，
在紧挨着v定义的注释里的词语很重要。v使用SharedMemoryAllocator，所以v分配来容纳它元素的内存将来自
共享内存，但v本身——包括它的全部数据成员——几乎将肯定不被放在共享内存里，v只是一个普通的基于
堆的对象，所以它将被放在运行时系统为所有普通的基于堆的对象使用的任何内存。那几乎不会是共享内存。
*/

 


