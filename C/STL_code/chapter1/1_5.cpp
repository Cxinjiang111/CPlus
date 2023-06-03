#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
//这就是仿函数 
/*
可以制造临时对象的方法是，在型别名称之后直接加一对小括号，并可指定初值 
shape(3,5) 相当于调用相应的构造函数且不指定对象名称。
*/
template<typename T>
class print{
public:
    void operator()(const T&elem){
        cout<<elem<<endl;
    }
};
int main(){
    int ia[6]={1,2,3,4,5,6};
    vector<int> a(ia,ia+6);
    for_each(a.begin(),a.end(),print<int>());

    return 0;
}