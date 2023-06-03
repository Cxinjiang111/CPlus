template<typename T,typename Allocator=allocator<T>>
class list{
private:
    Allocator alloc;
    class ListNode{
        T data;
        ListNode*prev;
        ListNode*next;
    };

};
template<typename T>
class allocator{
public:
    template<typename U>
    struct rebind{
        typedef allocator<U>other;
    }
};
allocator::rebind<ListNode>::other;
list<T> l;
/*
和我保持一致。每个分配器模板A（例如，std::allocator，SpecialAllocator，等）都被认为有一个叫做rebind的
内嵌结构体模板。rebind带有一个类型参数，U，并且只定义一个typedef，other。 other是A<U>的一个简单名
字。结果，list<T>可以通过Allocator::rebind<ListNode>::other从它用于T对象的分配器（叫做Allocator）获取对
应的ListNode对象分配器。
*/