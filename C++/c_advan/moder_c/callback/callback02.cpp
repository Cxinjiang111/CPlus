#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<cmath>
#include<functional>
using namespace std;
//这句话起始就是申明一种自定义函数类型 本质是种类型
//typedef int(*PFUN)(int a ,int b);
//typedef int(*PVFUN)(vector<int>&v);
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
//仿函数
struct divede{
    int operator()(int a,int b)
    {
        return a/b;
    }
};
class POW{
public:
//这里只能时静态函数才能被外部当函数指针使用
//    static int powe(int a,int b)
//     {
//         return pow(a,b);
//     }
    int powe(int a,int b)
    {
        return pow(a,b);
    }
private:
    int a;
    int b;
};
int main()
{
    //std::function<int(int,int)>把类型包装到在functional中，共同形成一种类型
    std::function<int(int,int)> p1=add;
    POW pw1;

    std::function<int(int,int)> pw=&(pw1.powe);
    std::function<int(vector<int>&)> p2=sub;   
    vector<int> v{1,2,3,4,5};
    function<int(int,int)> f3=[](int a,int b){return a*b;};
    map<string,std::function<int(int,int)>>bin={{"+",add},
    {"mult",[](int a,int b){return a*b;}},
    {"/",divede()},
    {"^",pw}
    };
    cout<<bin["+"](1,2)<<endl;

    cout<<bin["mult"](2,3)<<endl;
    cout<<bin["/"](8,4)<<endl;
    cout<<bin["^"](2,3)<<endl;
    //cout<<p2(v)<<endl;
    //cout<<p1(1,2)<<endl;

}
