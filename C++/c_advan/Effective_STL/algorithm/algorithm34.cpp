/*条款34：注意哪个算法需要有序区间*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<string>
using namespace std;
/*既可以和有序又可以和无序区间合作的算法很少，但当操作有序区间的时候它们最有用
有一个只能操作有序数据的算法的表：
binary_search   lower_bound
upper_bound     equal_range
set_union       set_intersection
set_difference  set_symmetric_difference
merge           inplace_merge
includes
最后一个需要有序区间的算法是includes。它用来检测是否一个区间的所有对象也在另一个区间中。因为
includes可能假设它的两个区间都已经有序，所以它保证了线性时间性能。没有那个保证，一般来说它会变慢。
unique ：从每个相等元素的连续组中去除第一个以外所有的元素。
换句话说，如果你要unique从一个区间去除所有重复值（也就是，让区间中所有值“唯一”），你必须先确
保所有重复值一个接着一个。猜到什么了？那是排序完成的东西之一。实际上，unique一般用于从区间中去
除所有重复值，所以你几乎总是要确保你传递给unique（或unique_copy）的区间是有序的。
                    只处理有序的
*/
void t1()
{
    vector<int> v;
    v.push_back(6);
    v.push_back(8);
    v.push_back(1);
    v.push_back(4);
    v.push_back(5);
    sort(v.begin(),v.end(),greater<int>());
    bool a5Exists=binary_search(v.begin(),v.end(),5);
/*
默认情况下，binary_search假设它搜索的区间是以“<”排序（也就是，值是升序），但在本例中，这个
vector是降序。当你在值的排列顺序和算法所期望的不同的区间上调用binary_search (或lower_bound等）会导
致未定义的结果时，你不该惊奇。
*/    
//binary_search(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __val, _Compare __comp)
bool b5Exists=binary_search(v.begin(),v.end(),5,greater<int>());

}







