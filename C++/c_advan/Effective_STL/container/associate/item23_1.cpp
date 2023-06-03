/*vector 替代map    pair<const K,V>
*/
#include<map>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

typedef pair<string,int> Data;
class DataCompare{
public:
    bool operator()(const Data&lhs,const Data&rhs)const
    {
        return keyLess(lhs.first,rhs.first);
    }
    //用於查找的比較函數
    bool operator()(const Data&lhs,const Data::first_type&k)const{
        return keyLess(lhs.first,k);
    }
    //用於查找的比較函數
    bool operator()(const Data::first_type &k,const Data&rhs)const{
        return keyLess(k,rhs.first);
    }
private:
    bool keyLess(const Data::first_type &k1,const Data::first_type&k2)const
    {
        return k1<k2;
    }
};
int main()
{
    vector<Data> vd; // 代替map<string, int>
 // 建立阶段：很多插入，
 // 几乎没有查找
sort(vd.begin(), vd.end(), DataCompare()); // 结束建立阶段。（当
 // 模拟multimap时，你
 // 可能更喜欢用stable_sort
 // 来代替；参见条款31。）
string s; // 用于查找的值的对象
// 开始查找阶段
if (binary_search(vd.begin(), vd.end(), s,
 DataCompare())) // 通过binary_search查找
vector<Data>::iterator i =
 lower_bound(vd.begin(), vd.end(), s,
 DataCompare()); // 在次通过lower_bound查找，
if (i != vd.end() && !DataCompare()(s, *i)) // 条款45解释了
 // “!DataCompare()(s, *i)”测试
pair<vector<Data>::iterator,
 vector<Data>::iterator> range =
 equal_range(vd.begin(), vd.end(), s,
 DataCompare()); // 通过equal_range查找
if (range.first != range.second)
... // 结束查找阶段，开始
 // 重组阶段
sort(vd.begin(), vd.end(), DataCompare()); // 开始新的查找阶段.
}


















