#include<iostream>
#include<string>
#include<vector>
using namespace std;
/*
令函数返回一个常量值，往往可以降低因客户错误而造成的意外，而又不至于放弃
安全性和高效性。
*/
class Rational{
public:
    const Rational operator*(const Rational &rhs);
};
//为了防止(a*b)=c;这种情况

/*const 成员函数
1，他们使class接口比较容易理解，得知哪个函数可以改动对象内容而哪个函数不行， 不太理解
2，使操作const对象成为可能，改善C++程序效率德一个根本办法是以pass by reference-to-const方式传递对象 
此技术的前提是const成员函数可用来处理取得的const对象
两个成员函数如果只是常量性不同，可以被重载
*/
class TextBlock{
public:
    TextBlock(std::string t):text(t){};
    //这个函数可以重载   这个返回必须是&类型
    //如果函数的返回类型是个内置类型，那么改动函数返回值从来就不合法
    //纵使合法，C++以by value 返回对象这一事实，意味被改动的其实是tb.text[0]的一个副本，不是tb.text[0]自身 那么也不会是你想要的行为
    const char &operator[](std::size_t position)const{
        cout<<"const"<<endl;
        return text[position];
    }
    char &operator[](std::size_t position){
        cout<<"non-const"<<endl;
        return text[position];
    }
private:
 std::string text;
};
/*
真实程序中const对象大多用于passed by pointer-to-const 或 passed by reference-to-const的传递结果
*/
int main()
{
    TextBlock tb("hello");
    std::cout<<tb[0];//调用非const版本 那么tb[0]具有non-const特性
    tb[0]='x';
    const TextBlock ctb("world"); 
    std::cout<<ctb[0];//调用const版本  那么tb[0]具有const特性 应为是返回值得到的  
    //ctb[0]='x';//error
    //感觉看情况，如果仅仅是打印 查看等等读操作，const可以避免误写的操作
    return 0;
}