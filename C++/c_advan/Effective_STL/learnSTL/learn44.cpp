/*条款44：尽量用成员函数代替同名的算法
关联容器提供了count、find、lower_bound、upper_bound和
equal_range，而list提供了remove、remove_if、unique、sort、merge和reverse
*/
#include<algorithm>
#include<iostream>
#include<list>
#include<deque>
#include<iterator>
#include<set>
using namespace std;
void t1()
{
    set<int> s;
    set<int>::iterator i=s.find(777);//set容器专属的成员函数
    set<int>::iterator i=find(s.begin(),s.end(),777);//使用algirithm中的算法
}
/*
对于标准的关联容器，选择成员函数而不是同名的算法有几个好处。首先，你得到的是对数时间而不是线性
时间的性能。其次，你判断两个元素“相同”使用的是等价，这是关联容器的默认定义。第三，当操纵map
和multimap时，你可以自动地只处理key值而不是(key, value)对。这三点给了优先使用成员函数完美的铁甲。
让我们转到list的与算法同名的成员函数身上。这里的故事几乎全部是关于效率的。每个被list作了特化的算法
（remove、remove_if、unique、sort、merge和reverse）都要拷贝对象，而list的特别版本什么都没有拷贝；它们
只是简单地操纵连接list的节点的指针。算法和成员函数的算法复杂度是相同的，但如果操纵指针比拷贝对象
的代价小的话，list的版本应该提供更好的性能。
*/









