#include<iostream>
using namespace std;
template<typename T>
class testclass{
public:
    static const int _datai=5;
    static const char _datal=3L;
    static const char _datac='c';
    static const int a;
};
/*
静态常量整数成员在class类内部直接初始化

*/
int main(){
    cout<<testclass<int>::_datai<<endl;
    cout<<testclass<int>::_datal<<endl;
    cout<<testclass<int>::_datac<<endl;
    //testclass<int>::_datai=8;//静态成员无法修改
}

