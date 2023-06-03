/*
不是从c中除去每个有特定值的物体，让我们消除下面判断式返回真的每个对象：
*/
//bool badValue(int x);// 返回x是否是“bad”
//对于序列容器（vector、string、deque和list），我们要做的只是把每个remove替换为remove_if，然后就完成了：
#include<vector>
#include<list>
#include<algorithm>
#include<set>
using namespace std;
bool badValue(int x);
int main()
{
    vector<int> c;
    list<int> l;
    //序列式容器vector,string,deque,list
    c.erase(remove_if(c.begin(),c.end(),badValue),c.end());
    //list時，這是去掉badValue最好的方法
    l.remove_if(badValue);
/*
“更容易但效率较低”的解决方案用remove_copy_if把我们需要的值拷贝到一个新容器中，
然后把原容器的内容和新的交换：
*/
    set<int> s;//標注的關聯容器
    set<int> goodValue;//用於容納不刪除的值的臨時容器
    remove_copy_if(s.begin(),s.end(), //從c拷貝不刪除的值到goodValues
    inserter(goodValue,goodValue.end()),badValue);
    s.swap(goodValue);//交換c和goodValues
/*
对这种方法的缺点是它拷贝了所有不删除的元素，而这样的拷贝开销可能大于我们感兴趣支付的。
我们可以通过直接从原容器删除元素来避开那笔帐单。不过，因为关联容器没有提供类似remove_if的成员函
数，所以我们必须写一个循环来迭代c中的元素，和原来一样删除元素。
*/

}
int main2()
{
    set<int> s;
    for(set<int>::iterator i=s.begin();i!=s.end();++i)
    {
        if(badValue(*i))
            s.erase(i);
    }
/*
唉，这有未定义的行为。当容器的一个元素被删时，指向那个元素的所有迭代器都失效了。当c.erase(i)返回
时，i已经失效。那对于这个循环是个坏消息，因为在erase返回后，i通过for循环的++i部分自增。
*/
}
int main2()
{
    set<int> s;
    for(set<int>::iterator i=s.begin();i!=s.end();)
    {
        //// 对于坏的值，把当前的i传给erase，然后作为副作用增加i；
        if(badValue(*i))
            s.erase(i++);
        else
            ++i;//对于好的值，只增加i
    }
}
