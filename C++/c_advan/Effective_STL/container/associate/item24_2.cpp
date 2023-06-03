#include<map>
using namespace std;
template<typename MapType,typename KeyArgType,typename ValueArgtype>
typename MapType::iterator effecientAddOrUpdate(MapType&m,const KeyArgType &k,ValueArgtype&v)
{
    typename MapType::iterator Ib=m.lower_bound(k);
    //// 如果Ib指向一个pair它的键等价于k
    if(Ib!=m.end()&&!(m.key_comp()(k,Ib->first)))
    {
        Ib->second=v;// 更新这个pair的值
        return Ib;//并返回指向pair的
    }
    else{
        typedef typename MapType::value_type MVT;
        return m.insert(Ib,MVT(k,v));// 把pair(k, v)添加到m并返回指向新map元素的迭代器
    }
}