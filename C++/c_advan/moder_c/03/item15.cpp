#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
#include<algorithm>
#include<array>
using namespace std;
void t1(){
    // int sz=3;// ⾮constexpr变量
    // int a[sz];
    // constexpr auto arraySize=sz;//sz的值在编译期不可知
    // constexpr int arraySize1=sz;

    // constexpr int sz=3; //这样做使得sz在编译期替换为常量 语句便可认识
    // constexpr auto arraySize=sz;
    // constexpr int arraySize1=sz;

    //int sz;
    //const auto arraySize=sz;
    //std::array<int,arraySize> data;//这里报错，就是const不具有constexpr的功能，不能替代
    //其实要区分constexpr是一种在编译器 让编译器处理问题时手段，也就是你给我在编译期把某种替换完成了，不替换，编译器就不知道
    //const更多是限制对一种东西的使用权 但constexpr既然在编译期就能确定并完成替换，那么在运行时就不会再去识别并修改，这就具有了const的只读不写的权力限制特性
    //但是constexpr在百年
}
constexpr int pow(int base,int exp)noexcept{
    return base*exp;    
}
void t2(){
    constexpr auto numConds=5;
    cout<<pow(3,numConds);
    // std::array<int ,pow(3,numConds)>result;
    // for(auto it=result.begin();it!=result.end();it++){
    //     cout<<*it<<endl;
    // }
    /*
假设我们需要⼀个数据结构来存储⼀个实验的结果，而这个实验可能以各种⽅式进⾏。实验期间⻛扇转
速，温度等等都可能导致亮度值改变，亮度值可以是⾼，低，或者⽆。如果有n个实验相关的环境条件。
它们每⼀个都有三个状态，最终可以得到的组合$$3^n$$个。储存所有实验结果的所有组合需要这个数
据结构⾜够⼤。假设每个结果都是int并且n是编译期已知的（或者可以被计算出的），⼀个
std::array是⼀个合理的选择。我们需要⼀个⽅法在编译期计算3^n。C++标准库提供了std::pow，
它的数学意义正是我们所需要的，但是，对我们来说，这⾥还有两个问题。第⼀，std::pow是为浮点
类型设计的 我们需要整型结果。第⼆，std::pow不是constexpr（即，使⽤编译期可知值调⽤得到的
可能不是编译期可知的结果），所以我们不能⽤它作为std::array的⼤小。
    
    */

}
/*
回忆下pow前⾯的constexpr没有告诉我们pow返回⼀个const值，它只说了如果base和exp是编译期
常量，pow返回值可能是编译期常量。如果base 和/或 exp不是编译期常量，pow结果将会在运⾏时计
算。这意味着pow不知可以⽤于像std::array的⼤小这种需要编译期常量的地⽅，它也可以⽤于运⾏
时环境：

*/
int main(){
    //t1();
    t2();

    return 0;
}   