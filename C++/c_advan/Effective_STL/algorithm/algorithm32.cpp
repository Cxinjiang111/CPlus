/*条款32：如果你真的想删除东西的话就在类似remove的算法后接上erase*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<string>
using namespace std;
void print(const vector<int>& w1)
{
    //这种排完序的前5个是有序的，后面的无序
    for(auto &it:w1)
    {
        cout<<it<<"\t";
    }
}
void t1()
{
    vector<int> v;
    v.reserve(10);
    for(int i=0;i<10;++i)
    {
         v.push_back(i);
    }
    v[3]=v[5]=v[9]=10;
    remove(v.begin(),v.end(),10);//没有99 没有删除元素
    /*              
    0 1 2 10 4 10 6     7   8  10
    0 1 2 4  6 7  8     7   8  10 
                       newend
remove 并不真的删除并对内存空间做处理，先把remove的数值向后移，不remove的数全部向前移。这样就剩最后的空间，该空间里原来的数值是啥就是啥
 ,并且remove返回一个新的end的迭代器的为未知    */
    
    cout<<v.size()<<endl;
    print(v);
}
void t2()
{
    vector<int> v;
    v.reserve(10);
    for(int i=0;i<10;++i)
    {
         v.push_back(i);
    }
    v[3]=v[5]=v[9]=10;
    v.erase(remove(v.begin(),v.end(),10),v.end());//没有99 没有删除元素 
    cout<<v.size()<<endl;
    print(v);
    /*              
    0 1 2 10 4 10 6     7   8  10
    0 1 2 4  6 7  8
    */
}
//remove 唯一能去除元素的函数真是list库的remove 函数

int main()
{
    t2();

    return 0;
}

















