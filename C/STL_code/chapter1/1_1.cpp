#include<iostream>
using namespace std;
template<class T>
struct testclass{
    testclass(){
        cout<<" testclass"<<endl;
    } 
};
int main(){
    testclass<int> obj1;//T->int 
    testclass<int*> obj2;//T->int*
    testclass<const int*> obj3;//T->const int*
/*
 testclass
 testclass
 testclass
*/
    return 0;
}
