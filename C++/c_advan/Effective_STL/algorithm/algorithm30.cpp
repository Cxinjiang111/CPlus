/*确保目标区间足够大
*/
#include<vector>
#include<iostream>
#include<algorithm>
#include<list>
using namespace std;
int transmogrify(int x)
{
    return 2*x;
}
void t1()
{
    vector<int>values;
    for(unsigned i=0;i<5;++i)
    {
        values.push_back(i+1);
    }
    vector<int>results(2);

    transform(values.begin(),values.end(),results.begin(),transmogrify);
    for(unsigned i=0;i<results.size();++i)
    {
        cout<<results[i]<<endl;
    }
    //output: 2   4   6   8   10
}
void t2()
{
    vector<int>values;
    for(unsigned i=0;i<5;++i)
    {
        values.push_back(i+1);
    }
    vector<int>results(2);
//transform(_InputIterator __first,_InputIterator __last,_OutputIterator __result,_UnaryOperation __unary_op)
    transform(values.begin(),values.end(),results.end(),transmogrify);//这个向result后面写的时候并没有报错
    for(unsigned i=0;i<results.size();++i)
    {
        cout<<results[i]<<endl;
    }
    //output: 0  0
    /*
transform被告知它的目的区间是从results.end()开始的，所以那就是开始写在values的每个元素上调
用transmogrify的结果的地方。就像所有使用目标区间的算法，transform通过对目标区间的元素赋值的方法写
入结果，transform会把transmogrify应用于values[0]并把结果赋给*results.end()。然后它会把transmogrify应用于
value[1]并把结果赋给*(results.end()+1)。那只能带来灾难，因为在*results.end()没有对象，*(results.end()+1)也
没有！调用transform是错误的，因为它会给不存在的对象赋值。（条款50解释了STL的一个调试实现怎么在运
行期检测这个问题。）犯了这种错误的程序员几乎总是以为他们调用算法的结果能插入目标容器。如果那是
你想要发生的，你就必须说出来。STL是一个库，不是一个精神。在本例中，说“请把transform的结果放入
叫做results容器的结尾”的方式是调用back_inserter来产生指定目标区间起点的迭代器：   
    */
}
void t3()
{
    vector<int>values;
    for(unsigned i=0;i<5;++i)
    {
        values.push_back(i+1);
    }
    vector<int>results(5);
//transform(_InputIterator __first,_InputIterator __last,_OutputIterator __result,_UnaryOperation __unary_op)
    //transform(values.begin(),values.end(),back_inserter(results),transmogrify);//这个向result.end的后面添加，调用operator++函数-》push_back
    for(unsigned i=0;i<results.size();++i)
    {
        cout<<results[i]<<endl;
    }
/*
0
0
0
0
0
2
4
6
8
10
*/
}
void t4()
{
    vector<int>values;
    for(unsigned i=0;i<5;++i)
    {
        values.push_back(i+1);
    }
    list<int> l;
//transform(_InputIterator __first,_InputIterator __last,_OutputIterator __result,_UnaryOperation __unary_op)
    transform(values.begin(),values.end(),front_inserter(l),transmogrify);//实现倒序插入，vector没有front_inserter
    
    for(auto &resl:l)
    {
        cout<<resl<<"\t";
    }
    //output:   10      8       6       4       2
}
/*
front_inserter让你强制算法在容器前端插入它们的结果，back_inserter让你告诉它们把结果放在容器后端，有
点惊人的是inserter允许你强制算法把它们的结果插入容器中的任意位置：
*/
void t5()
{
    vector<int>values;
    for(unsigned i=0;i<5;++i)
    {
        values.push_back(i+1);
    }
    list<int> l;
//transform(_InputIterator __first,_InputIterator __last,_OutputIterator __result,_UnaryOperation __unary_op)
    transform(values.begin(),values.end(),front_inserter(l),transmogrify);//实现倒序插入，vector没有front_inserter
    
    for(auto &resl:l)
    {
        cout<<resl<<"\t";
    }
}
void t6()
{
    vector<int>values;
    vector<int>results;
    for(unsigned i=0;i<5;++i)
    {
        values.push_back(i+1);
        results.push_back(i*3);
        results.push_back(i*30);
    }
    results.reserve(results.size()+values.size());
    transform(values.begin(),values.end(),inserter(results,results.begin()+results.size()/2),transmogrify);
    for(auto &resl:results)
    {
        cout<<resl<<"\t";
    }
    //output:
//0       0       3       30      6       2       4       6       8       10      60      9       90      12      120
}
void t7()
{
    vector<int>values;
    vector<int>results;
    for(unsigned i=0;i<5;++i)
    {
        values.push_back(i+1);
        results.push_back(i*3);
    }
    results.reserve(results.size()+values.size());
    transform(values.begin(),values.end(),results.begin(),transmogrify);//result的中values.size()的值会被覆盖掉
    for(auto &resl:results)
    {
        cout<<resl<<"\t";
    }
    //output:
//
}
int main()
{
    
    t7();

    return 0;
}














