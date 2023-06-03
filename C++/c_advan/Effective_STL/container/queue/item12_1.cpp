/*
一个更面向对象的解决方案是创建一个Lock类，在它的构造函数里获得互斥量并在它的析构函数里释放它，
这样使getMutexFor和releaseMutexFor的调用不匹配的机会减到最小。这样的一个类（其实是一个类模板）基
本是这样的：
*/
#include<iostream>
#include<vector>
#include<set>
#include<list>
#include<map>
#include<algorithm>
#include<mutex>

using namespace std;
class Container1{

};
template<typename Container>
class Lock{
public:
    Lock(const Container container):c(container){
        getMutexFor(c);
    }

    ~Lock()
    {
        releaseMutexFor(c);
    }

private:
    const Container&c;
};
int main()
{
    vector<int> v;
    {   //鎖的一個區域快
        Lock<vector<int>> lock(v);
        vector<int>::iterator first(find(v.begin(),v.end(),5));//行1
        if(first!=v.end())//行2
        {
            *first=0;//行3
        }
    }//自動析構掉 釋放玩鎖
}