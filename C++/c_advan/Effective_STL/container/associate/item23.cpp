/*考虑用有序vector代替关联容器
*/
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
class Widget{

};
//vector 替代set
int main()
{
    vector<Widget> vw;//代替set<Widget>
    // 建立阶段：很多插入，
    // 几乎没有查找

    sort(vw.begin(),vw.end());
    // 结束建立阶段。（当
    // 模拟一个multiset时，你
    // 可能更喜欢用stable_sort
    // 来代替；

    Widget w;
    if(binary_search(vw.begin(),vw.end(),w));
    vector<Widget>::iterator i=lower_bound(vw.begin(),vw.end(),w);
    if(i!=vw.end()&&!(w<*i))


    std::pair<vector<Widget>::iterator,vector<Widget>::iterator> range=equal_range(vw.begin(),vw.end(),w);
    if(range.first!=range.second)


    return 0;
}












