#include<iostream>
using namespace std;
// 1
template<class T>
struct testclass{
    testclass(){
        cout<<" testclass"<<endl;
    } 
};
// 2 模板特殊化
template<class T>
struct testclass<T*>
{
    testclass(){
        cout<<" testclass<T*>"<<endl;
    }    
};
// 3 
template<class T>
struct testclass<const T*>{
    testclass(){
        cout<<"testclass<const T*>"<<endl;
    }    
};
int main(){
    testclass<int> obj1;//T->int  1
    testclass<int*> obj2;//T->int  2
    testclass<const int*> obj3;//T->int  3
//编译器会不仅会根据T选择而且会根据类模板选择
/*
testclass
testclass<T*>
testclass<const T*>
*/
    return 0;
}
