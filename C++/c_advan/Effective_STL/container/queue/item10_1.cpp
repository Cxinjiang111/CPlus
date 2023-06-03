#include<iostream>

void*operator new(size_t btypes);

//返回指針
pointer allocator<T>::allocate(size_type numObjects);

/*
两者都带有一个指定要分配多少内存的参数，但对于operator new，这个参数指定的是字节数，而对于
allocator<T>::allocate，它指定的是内存里要能容纳多少个T对象。例如，在sizeof(int) == 4的平台上，如果你要
足够容纳一个int的内存，你得把4传给operator new，但你得把1传给allocator<int>::allocate。（在operator new情
况下这个参数的类型是size_t，而在allocate的情况下它是allocator<T>::size_type。在两种情况里，它都是无符号
整数类型，通常allocator<T>::size_type是一个size_t的typedef。）关于这个差异没有什么“错误”，但是
operator new和allocator<T>::allocate之间的不同协定使应用自定义operator new的经验到开发自定义分配器的过
程变得复杂。

operator new和allocator<T>::allocate的返回类型也不同。operator new返回void*，那是C++传统的表示一个到未
初始化内存的指针的方式。allocator<T>::allocate返回一个T*（通过pointer typedef），不仅不传统，而且是有
预谋的欺诈。从allocator<T>::allocate返回的指针并不指向一个T对象，因为T还没有被构造！在STL里暗示的
是希望allocator<T>::allocate的调用者将最后在它返回的内存里构造一个或多个T对象（也许通过allocator<T>::
construct，通过uninitialized_fill或通过raw_storage_iterator的一些应用），虽然在这里没有发生vector::reserve或
string::reserve（参见条款14）。在operator new和allocator<T>::allocate之间返回类型的不同使未初始化内存的概
念模型发生了变化，而它再次使把关于实现operator new的知识应用到开发自定义分配器变得困难。
*/

list<int> L; // 和list<int, allocator<int> >一样；allocator<int>从未用来 分配内存！
set<Widget, SAW> s; // 记住SAW是一个 SpecialAllocator<Widget>的typedef；SAW从未分配内存！
/*
这个怪癖对list和所有标准关联容器都是真的（set、multiset、map和multimap）。那是因为这些是基于节点的
容器，即，这些容器所基于的数据结构是每当值被储存就动态分配一个新节点。对于list，节点是列表节点。
对于标准关联容器，节点通常是树节点，因为标准关联容器通常用平衡二叉搜索树实现。
*/
template<typename T,typename Alocator=allocator<T>>
class list{
private:
    Allocator alloc;
    class ListNode{
        T data;
        ListNode*prev;
        ListNode*next;
    };

};
/*
当添加一个新节点到list时，我们需要从分配器为它获取内存，我们要的不是T的内存，我们要的是包含了一
个T的ListNode的内存。那使我们的Allocator对象没用了，因为它不为ListNode分配内存，它为T分配内存。现
在你理解list为什么从未让它的Allocator做任何分配了：分配器不能提供list需要的。

list需要的是从它的分配器类型那里获得用于ListNode的对应分配器的方法。按照协定，分配器得提供完成那
个工作的typedef，否则将会很难办。那个typedef叫做other，但它不那么简单，因为other是嵌入一个叫做
rebind的结构体的typedef，rebind自己是一个嵌入分配器的模板——分配器本身也是模板！
*/
template<typename T>
class Allocator{
public:
    template<typename U>
    struct rebind{
        typedef allocator<U>other;
    }
};
Allocator::rebind<ListNode>::other;