#include<iostream>
#include<vector>
void *mallocShared(size_t bytesNeeded)
{
    return malloc(bytesNeeded);
}
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
typedef std::vector<int,SharedMemoryANocator<int>> shareDoubleVec;
int main()
{
    //分配足夠的共享内存來容納一個shareDoubleVec對象 
    void*pVectorMemory=mallocShared(sizeof(shareDoubleVec));
    //使用placement new來在那塊内存中建立一個SharedDoubleVec對象
    shareDoubleVec *pv=new(pVectorMemory)shareDoubleVec;  

    pv->~vector();//銷毀共享内存中的對象
    freeShared(pVectorMemory);//銷毀原理啊的共享内存快

}
/*
我希望那些注释让你清楚是怎么工作的。基本上，你获得一些共享内存，然后在里面建立一个用共享内存为
自己内部分配的vector。当你用完这个vector时，你调用它的析构函数，然后释放vector占用的内存。代码不很
复杂，但我们在上面所做的比仅仅声明一个本地变量要苛刻得多。除非你真的要让一个容器（与它的元素相
反）在共享内存里，否则我希望你能避免这个手工的四步分配/建造/销毁/回收的过程。
在这个例子里，无疑你已经注意到代码忽略了mallocShared可能返回一个null指针。显而易见，产品代码必须
考虑这样一种可能性。 此外，共享内存中的vector的建立由“placement new”完成。
*/






