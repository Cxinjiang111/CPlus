//函数实参
#include<iostream>
using namespace std;
void someFun(int ,double);//someFun是一个函数，类型是void (int ,double)
template<typename T>
void f1(T param){ //传值
    cout<<"ok this is f1"<<endl;
}
template<typename T>
void f2(T &param){//传引用
    cout<<"ok this is f2"<<endl;
}
void t1(){
    //这样就穿不了值，感觉不是掉somefun 而是调用f1,f2 ,somefun做了傀儡似的
    f1(someFun);//param被推导为指向函数的指针，void(*)(int,double)
    f2(someFun);//param被推导为指向函数的引用，void(&)(int,double)
}
/*
在模板类型推导时，有引⽤的实参会被视为⽆引⽤，他们的引⽤会被忽略
对于通⽤引⽤的推导，左值实参会被特殊对待
对于传值类型推导，实参如果具有常量性和易变性会被忽略
在模板类型推导时，数组或者函数实参会退化为指针，除⾮它们被⽤于初始化引⽤
*/
void someFun(int ,double){
    for(int i=0;i<3;i++){
        cout<<"hello i am someFun"<<endl;
    }
}
int main(){
    t1();
    //ok this is f1
    //ok this is f2
    return 0;
}