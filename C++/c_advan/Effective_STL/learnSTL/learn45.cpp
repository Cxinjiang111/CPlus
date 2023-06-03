/*条款45：注意count、find、binary_search、lower_bound、upper_bound和equal_range的区别

未完待续。。。。。。 实在不想看了，太累了。赶快结束把



你要寻找什么，而且你有一个容器或者你有一个由迭代器划分出来的区间——你要找的东西就在里面。你要
怎么完成搜索呢？你箭袋中的箭有这些：count、count_if、find、find_if、binary_search、lower_bound、
upper_bound和equal_range。面对着它们，你要怎么做出选择？
*/
/*
，count这个惯用法编码起来比较简单。但是，当搜索成功时，它的效率比较低，因
为当找到匹配的值后find就停止了，而count必须继续搜索，直到区间的结尾以寻找其他匹配的值。
使用equal_range。equal_range返回一对迭代器，第一个等于lower_bound返回的迭代
器，第二个等于upper_bound返回的
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
    vector<int> vw;
    sort(vw.begin(),vw.end());
    typedef vector<int>::iterator VWIter;
    typedef pair<VWIter,VWIter> VWIterPair;
    VWIterPair p=equal_range(vw.begin(),vw.end(),5);
    if(p.first!=vw.end())
    {

    }
}
/*
在区间中寻找一个位置。比如，假设我们有一个Timestamp类和一个Timestamp的vector，
它按照老的timestamp放在前面的方法排序：
*/
int main()
{

}
