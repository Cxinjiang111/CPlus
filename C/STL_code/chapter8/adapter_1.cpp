#include<algorithm>
#include<functional>
#include<vector>
#include<iostream>
#include<iterator>
using namespace std;
void print(int i)
{
    cout<<i<<" ";
}
class Int{
public:
    explicit Int(int i):m_i(i){}
    void print1()const{cout<<'['<<m_i<<"]"<<endl;}
private:
    int m_i;
};
int main()
{
    ostream_iterator<int> outite(cout," ");
    int ia[6]={2,21,12,7,19,23};
    vector<Int> iv; 
    for(auto i:ia){
        iv.push_back(Int(i));
    }

        //mem_fun_ref这样就可以将类中任一函数 当成仿函数来使用
    for_each(iv.begin(),iv.end(),mem_fun_ref(&Int::print1));
}