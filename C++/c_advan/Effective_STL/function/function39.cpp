/*条款39：用纯函数做判断式
没太懂

*/
#include<numeric>
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<set>
#include<deque>
#include<string>
#include<iterator>
using namespace std;
class Widget{

};
class BadPredicate:public unary_function<int,void>
{
public:
    BadPredicate():timesCalled(0){}
    bool operator()(const int&){
        return ++timesCalled==3;
    }
private:
    size_t timesCalled;
};
template<typename FwdIterator,typename Predicate>
FwdIterator remove_if1(FwdIterator begin,FwdIterator end,Predicate p)
{
    begin=find_if(bein,end,p);
    if(begin==end)//没有找到
    {
        return begin;
    }   
    else{ //找到了
        FwdIterator next=begin;//
        return remove_copy_if(++next,end,begin,p);
    }
}
int main()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
    v.push_back(3);            
    v.push_back(3);    
    v.push_back(2);           
    v.push_back(3);   
    v.push_back(1);
    v.push_back(1);         
    v.erase(remove_if(v.begin(),v.end(),BadPredicate()),v.end());
    for (size_t i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<"\t";
    }
    cout<<endl;

    return 0;
}