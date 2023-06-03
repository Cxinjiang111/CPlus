#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
#include<algorithm>
#include<array>
using namespace std;
//35法则
class Widget{
public:
    Widget(Widget&&rhs);
    Widget& operator=(Widget&rhs);
};
class Base{
public:
    virtual ~Base()=default;
    Base(Base&&)=default;
    Base&operator=(Base&&)=default;
    Base(const Base&)=default;
    Base&operator=(const Base&)=default;
};
