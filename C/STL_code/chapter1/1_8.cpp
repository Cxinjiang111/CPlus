#include<iostream>
#include<vector>
using namespace std;
//前闭后开区间表示法[first, last) 迭代器
template<class InputIterator,class T>
InputIterator find_(InputIterator first,InputIterator last,const T&value){
    while (first!=last&&*first!=value)
    {
        ++first;
    } 
    return first;      
}
template<class InputIterator,class Function>
//两个迭代器， 也就是指针，加入一个操作的函数 
Function for_each_(InputIterator first,InputIterator last,Function f){
    for(;first!=last;++first){
        f(*first);
    }
    return f;
}
template<typename T>
void print(T& a){
    cout<<a<<endl;
}
int main(){
    vector<int> a{1,2,3,4,5};
    for_each_(a.begin(),a.end(),print<int>);

    return 0;
}




