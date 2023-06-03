#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
#include<algorithm>
using namespace std;
class Widget{

};
void t1(){
    std::vector<Widget> vw;
    Widget w1;
    vw.push_back(w1);
}
template<class T, size_t N>
void swap(T (&a)[N],T(&b)[N])noexcept(noexcept(swap(*a,*b)));
template<class T1,class T2>
struct pair{
    void swap(pair&p)noexcept(noexcept(swap(first,p.first))&&
    noexcept(swap(second,p.second)));
};
