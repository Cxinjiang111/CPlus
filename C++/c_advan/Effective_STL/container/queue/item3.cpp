#include<vector>
#include<algorithm>
#include<list>
#include<map>
#include<string>
using namespace std;
class Widget{
public:
    Widget();
    Widget(const Widget&);//拷贝构造函数
    Widget&operator=(const Widget&);//拷贝赋值操作符

};
/*
当然由于继承的存在，拷贝会导致分割。那就是说，如果你以基类对象建立一个容器，而你试图插入派生类
对象，那么当对象（通过基类的拷贝构造函数）拷入容器的时候对象的派生部分会被删除：

*/
class SpecialWidget:public Widget{
public:
    SpecialWidget():Widget::Widget(){};
};

void fun()
{
    vector<Widget> vw;
    SpecialWidget sw;
    vw.push_back(sw);//基类的容器插入继承类的容器。派生类派生的部分会被删除
    //分割问题暗示了把一个派生类对象插入基类对象的容器几乎总是错的。
}
/*一个使拷贝更高效、正确而且对分割问题免疫的简单的方式是建立指针的容器而不是对象的容器。也就是
说，不是建立一个Widget的容器，建立一个Widget*的容器。拷贝指针很快，它总是严密地做你希望的（指针
拷贝比特），而且当指针拷贝时没有分割。不幸的是，指针的容器有它们自己STL相关的头疼问题。你可以
从条款7和33了解它们。如果你想避免这些头疼并且仍要避开效率、正确性和分割问题，你可能会发现智能指
针的容器是一个吸引人的选择，请转到条款7。*/ 

