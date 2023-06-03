//std::iterator的保证
/*
任何迭代器都应该提供五个内嵌相应型别，以利于traits 萃
取，否则便是自别于整个STL架构，可能尤法与其它STL组件顺利搭配。
然而写 代码难免挂－漏万，谁也不能保证不会有粗心大意的时候。
如果能够将事情简化，就好多了。STL提供了一个iteratorsclass如下，
如果每个新设计的迭代器都继承自它，就可保证符合STL所需之规范：
*/
template<class Category,class T,class Distance,class Pointer=T*,class Reference=T&>
struct iterator{
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};
/*
iterator class不含任何成员，纯粹只是型别定义，所以继承它并不会招致任 何额外负担。
由于后三个参数皆有默认值，故新的迭代器只需提供前两个参数即可。
先前3.2节土法炼钢的Listiter,如果改用正式规格，应该这么写：
*/
template<class Item>
//  `                                    Category               T
struct ListIter:public std::iterator<std::forward_iterator_tag,Item>
{

};


