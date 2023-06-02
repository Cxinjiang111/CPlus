/*
item3_2出现的问题导致所谓的logical constness 
一个const成员函数可以修改他所处理的对象内的某些bits 但只有在客户端
侦测不出的情况下才的如此
*/
#include<iostream>
#include<string>
#include<string.h>
using namespace std;
class CTextBlock{
public:
    CTextBlock(char* t):pText(t){};

    std::size_t length() const;

private:
    char*pText;
    mutable std::size_t textLength;//不加mutable 下面函数回报错，
    mutable bool lengthIsValid;//现在 这些成员变量可能总是回被改变 即使在const成员函数内
};
std::size_t CTextBlock::length() const //这是个const 函数
{
    if(!lengthIsValid)
    {
        textLength=strlen(pText);//error
        lengthIsValid=true;
    }
    return textLength;
}
//对比 
class CTextBlock1{
public:
    CTextBlock1(char* t):pText(t){};

    std::size_t length() ;
private:
    char*pText;
     std::size_t textLength;//不加mutable 下面函数不会报错，
     bool lengthIsValid;//现在 这些成员变量可以被改变 
};
std::size_t CTextBlock1::length() //这是个非const 函数
{
    if(!lengthIsValid)
    {
        textLength=strlen(pText);//error
        lengthIsValid=true;
    }
    return textLength;
}
