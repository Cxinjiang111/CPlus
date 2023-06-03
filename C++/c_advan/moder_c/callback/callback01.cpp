#include<iostream>
#include<vector>
#include<functional>
using namespace std;
//这句话起始就是申明一种自定义函数类型 本质是种类型
typedef int(*PFUN)(int a ,int b);
typedef int(*PVFUN)(vector<int>&v);
int add(int a,int b)
{
    return a+b;
}

int sub(vector<int>&v)
{
    int sum=0;
    for(int i=0;i<v.size();++i)
    {
    sum+=v[i];
    }
    return sum;
}
int main()
{
    vector<int> v{1,2,3,4,5};
    PVFUN p=sub;
    PFUN p2=add;
    cout<<p(v)<<endl;
    cout<<p2(1,2)<<endl;

}
