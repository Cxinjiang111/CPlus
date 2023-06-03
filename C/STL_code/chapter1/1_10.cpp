#include<iostream>
using namespace std;
//记住仿函数的格式
template<class T>
struct Plus{
    T operator()(const T&x,const T&y){
        return x+y;
    }
    T m_a;
};
template<class T>
struct Min{
    bool operator()(const T&x,const T&y){
        return x<y;
    }
};
int main(){
    Plus<int> p;
    Min<int> m;
    cout<<p(3,5)<<endl;
    cout<<m(3,5)<<endl;
}




