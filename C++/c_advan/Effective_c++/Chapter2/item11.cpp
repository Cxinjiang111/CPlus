/*
在operator=中处理“自我赋值”
*/
//自我赋值发生在对象被赋值给自己时。
#include<iostream>
#include<algorithm>
#include<iterator>
class Bitmap{

};
class Widget{
public:
    Widget&operator=(const Widget &rhs);
    Widget&operator=( Widget rhs);
private:
    Bitmap *pb;
};
Widget&Widget::operator=(const Widget&rhs)
{
    delete pb;
    pb =new Bitmap(*rhs.pb);
    return *this;
}

Widget&Widget::operator=(const Widget&rhs)
{
    if(this==&rhs) return *this;
    delete pb;
    pb =new Bitmap(*rhs.pb);
    return *this;
}


Widget&Widget::operator=(const Widget&rhs)
{
    Bitmap *pOrig=pb;
    pb =new Bitmap(*rhs.pb);
    delete pOrig;
    return *this;
}

Widget&Widget::operator=(const Widget&rhs)
{
    Widget temp(rhs);
    std::swap(temp,*this);
    return *this;
}


Widget&Widget::operator=(Widget rhs)
{
    std::swap(rhs,*this);
    return *this;
}
