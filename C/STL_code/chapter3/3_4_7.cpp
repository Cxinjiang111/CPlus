#include<iostream>
using namespace std;
struct B{};
struct D1:public B{};
struct D2:public D1{};
//这说明了根据类型来进行重载决议
template<typename I>
void func(I&p,B){
cout<<"B"<<endl;
}
template<typename I>
void func(I&p,D2){
cout<<"D2"<<endl;
}
int main(){
    int* p;
    func(p,B());
    func(p,D1());
    func(p,D2());

    return 0;
}
