/* 条款42：确定less<T>表示operator<  */
#include<vector>
#include<algorithm>
#include<iostream>
#include<list>
#include<set>
#include<string>
#include<iterator>
#include<functional>
using namespace std;
class widget{
public:
    size_t weight()const;
    size_t maxSpeed()const;

};
bool operator<(const widget&lhs,const widget&rhs)
{
    return lhs.weight()<rhs.weight();
}
//less特化
template<>
struct std::less<widget>:public std::binary_function<widget,widget,bool>
{
    bool operator()(const widget&lhs,const widget&rhs){
        return lhs.maxSpeed()<rhs.maxSpeed();
    }
};
struct MaxSpeedCompare:public binary_function<widget,widget,bool>
{
    bool operator()(const widget&lhs,const widget&rhs)
    {
        return lhs.maxSpeed()<rhs.maxSpeed();
    }

};
int main()
{
    vector<widget> vw;
    sort(vw.begin(),vw.end(),MaxSpeedCompare());

    multiset<widget,MaxSpeedCompare>mw;
}














