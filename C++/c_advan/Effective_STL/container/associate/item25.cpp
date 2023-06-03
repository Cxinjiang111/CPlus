/*
熟悉非标准散列容器

散列容器是关联容器，因此你不该惊讶，正如所有关联容器，它们需要知道储存在容器中的对象类型，用于
这些对象的比较函数，以及用于这些对象的分配器。另外，散列容器需要散列函数的说明。下面是散列容器
声明：
*/

#include<iterator>
#include<hashtable.h>
#include<hash_fun.h>
#include<algorithm>
using namespace std;
template<typename T,typename HashFunction,typename CompareFunction,typename Allocator=allocator<T>> 
class hash_container{};
/*
这非常接近于散列容器的SGI声明，主要差别是SGI为HashFunction和CompareFunction提供了默认类型。
hash_set的SGI声明看起来基本上像这样
*/
template<typename T,typename HashFunction=hash<T>,typename CompareFunction=equal_to<T>,typename Allocator=allocator<T>> 
class hash_container{};
/*
SGI设计的一个值得注意的方面是使用equal_to作为默认比较函数。这违背标准关联容器的约定——默认比较
函数是less。这个设计结果不仅仅表示简单地改变默认比较函数。SGI的散列容器确定在一个散列容器中的两
个对象是否有相同的值是通过相等测试，而不是等价（参见条款19）。对于散列容器来说，这不是一个不合
理的决定，因为散列关联容器，不像它们在标准中的（通常基于树）兄弟，不需要保持有序。
*/

template<typename T,typename HashingInfo=hash_compare<T,less<T>>,typename Allocator=allocator<T>>
class hash_container{};
/*
这种接口设计有趣的地方是HashingInfo的使用。容器的散列和比较函数储存在那里，但HashingInfo类型也容
纳了控制表中桶（bucket）最小数量，以及容器元素对桶的最大允许比率的枚举。当这比率被超过时，表中
桶的数量就增加，而表中的一些元素需要重新散列。（SGI提供具有类似控制表中桶和表中元素对桶比率的
成员函数。）（译注：如果你不知道桶和散列表的原理，那么看看数据结构的书中关于散列表的部分。）
*/





