/*deque采用一块所谓的map（非STL的map容器）作为主控，这里的map是一小块
//连续空间，其中每个元素都是指针，指针指向另一段较大的连续性空间，成为缓冲区，
//缓冲区才是deque的存储空间主体，
map其实是一个T**，也就是他是一个指针，所指之物又是一个指针，指向型别为T的一块空间


*/
template<class T,class Alloc=alloc,size_t BufSiz=0>
class deque{
public:
    typedef T value_type;
    typedef value_type*pointer;

protected:
    //元素指针的指针
    typedef pointer*map_pointer;

    map_pointer map;//指向map，map是块连续空间，其内的每个元素都是
                    //指向一个指针（称为结点），指向一块缓冲区
    size_type map_size;//mao内可容纳多少个指针


};