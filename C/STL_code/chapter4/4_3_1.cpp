//list的好处是每次插入或删除一个元素，旧配置或释放一个空间，所以list对于空间的
//运用有绝对的精准，一点也不浪费
//双向链表
template<class T>
struct __list_node{
    typedef void *void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};