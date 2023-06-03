#include<iostream>
#include<vector>
using namespace std;
class alloc{
};
template<class T,class Alloc=alloc,size_t Bufsize=0>
class deque{
public:
    deque(){cout<<"deque"<<endl;}
};
//书上的这个程序运行不出来 ？？？？？
template<class T,class Sequence=vector<T>>
class stack{
    friend bool operator==(const stack<T,Sequence>&,const stack<T,Sequence>&);
public:
    stack(){cout<<"stack"<<endl;}
    stack(Sequence&c_):c(c_){}
private:
    Sequence c;
};
template<class T,class Sequence=vector<T>>
bool operator==(const stack<T,Sequence<T>>& lhs,const stack<T,Sequence>& rhs){
    // for(auto s:lhs){
    //     cout<<s<<endl;
    // }
    cout<<"operator=="<<endl;
    return true;
}
int main(){
    vector<int> aa{1,2,3,4,5};
    stack<int,vector<int>> m1(aa);
    stack<int,vector<int>> m2(aa);
    m1==m2;
    return 0;
}