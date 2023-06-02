/*
尽可能使用const 
*/
#include<iostream>
#include<vector>
using namespace std;

int main2()
{
    char greeting[]="hello";
    char*p=greeting;
    const char*p=greeting;//non-const pointer const data;
    char* const p=greeting;//const pointer non-const data;
    const char* const p=greeting;//const pointer const data;
    //const 出现在*左边，表示被指物式常量。 出现在*右边表示指针自身式常量，如果两边都出现，则都是常量

}

//如果被指物是常量，cosnt在*前后没有区别
void f1(const int*pw)
{
    int  a=3;
    pw=&a;
}
void f2(int*const pw)
{
    // int  a=3;
    // pw=&a;//error
    *pw=7;
}
//STL 迭代器的运用
void m()
{
    std::vector<int> vec;
    const std::vector<int>::iterator iter=vec.begin();
    *iter=10;// 所指的值可改变
    //++iter;//error;迭代器不可改变移动
    std::vector<int>::const_iterator iter1=vec.begin();
   // *iter1=22;//error所指的值不可改变
    ++iter1; //迭代器可改变移动
}
