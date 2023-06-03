#include<iostream>
using namespace std;
template<class InputIterator,class OutputIterator>
OutputIterator copy(InputIterator first,InputIterator end,OutputIterator result) //你要改造输出迭代器
{
    for(;first!=end;++result,++first)
    {
        *result=*first;
    }
    return result;//返回迭代器的位置

}   
template<class T>
class ostream_iterator{
private: 
    ostream *os;
    const char *string;
public:
    ostream_iterator(ostream&s,const char*c):os(&s),string(c){}
    ostream_iterator(const ostream_iterator& out):os(out.os),string(out.string){}
    //输出迭代器具有可写性，输入迭代行具有可读性 
    ostream_iterator &operator=(const ostream_iterator &out) //接受一个迭代器
    {
        os=out.os;
        string=out.string;
        return os;
    }
    //执行
    ostream_iterator<T>&operator=(const T&value)//接受一个值，需要输出该value
    {
        *os<<value;
        if(string)
            *os<<string;
        return *this;
    } //此处的复制确实就是把传入的值送入到迭代器os中，进而送到标准库的输出迭代器中
    ostream_iterator<T>&operator*(){return *this;}
    ostream_iterator<T>&operator++(){return *this;}
    ostream_iterator<T>&operator++(int){return *this;}
};
int main()
{
    ostream_iterator<string> s(cout,"hello");
    s="you are world";

}


