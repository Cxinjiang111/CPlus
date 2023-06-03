#include<assert.h>
#include<iostream>
using namespace std;
class Rectangle{
public:
    virtual void setHeight(int newHeight);
    virtual void setWidth(int newWidth);
    virtual int height()const;
    virtual int width()const;
};
void makeBigger(Rectangle&r)
{
    int oldHeight=r.height();
    r.setHeight(r.width()+10);
    assert(r.height()==oldHeight);
}
class Square:public Rectangle{

};
void fun()
{
    Square s;
    assert(s.width()==s.height());
    makeBigger(s);
    assert(s.width()==s.height());
}
/*
我们遇到一个问题，如何调解下面各个assert判断式
调用makeBigger之前，s的高度和宽度相同；
在makeBigger函数内， s的宽度改变，但高度不变

*/

