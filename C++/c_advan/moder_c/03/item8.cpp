#include<iostream>
using namespace std;
void f(int a){
cout<<"f(int a)"<<endl;
}
void f(void* p){
    cout<<"f(void* p)"<<endl;
}
int main(){
    f(0);
    //f(NULL);//编译报错，现代编译器认为是由奇异的
    f(nullptr);//output f(void* p)
    return 0;
}