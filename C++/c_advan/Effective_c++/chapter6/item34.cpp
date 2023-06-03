/*区分接口继承和实现继承
接口继承和实现继承不同。在public继承之下，derived classes总是继承base class 的接口。
pure virtual函数只具体指定接口继承。
简朴的（非纯）impure virtual函数具体指定接口继承及缺省实现继承。
non-virtual函数具体指定接口继承以及强制性实现继承。
*/
/*
身为class设计者，有时候你会希望derived classes只继承成员函数的接口（也就是声明）；
有时候你又会希望derived classes同时继承函数的接口和实现，但又 希望能够覆写(override)它们所继承的实现；
义有时候你希望derived classes同时继承函数的接口和实现， 并目小允许覆写任何东西。
*/
#include<string>
#include<iostream>
using namespace std;
class Shape{
public:
    Shape();
    virtual void draw()const=0;//纯虚函数  所以不能构建Shape class的实体，只能创建其derived class的实体
    //纯虚函数 他们必须被任何“继承了他们”的具象class重新申明，而且他们在抽象中class中通常没有定义，
    //申明一个纯虚函数的目的就是让derived classes只继承函数接口  必须在继承类中声明，强制的
    /*
这对Shape::draw函数是再合理不过的事了，因为所有Shape对象都应该是可   
绘出的，这是合理的要求。但Shape class无法为此函数提供合理的缺省实现，毕竟
椭圆形绘法迥异于矩形绘法。Shape::draw的声明式乃是对具象derived classes设
“计者说，你必须提供一个draw函数，但我不干涉你怎么实现它。”   
    */
    virtual void error(const std::string&msg);//非纯虚函数 继承类中如果没有重写该函数，那么调用基类中的，在继承类中并不一定是强制的
    //继承类中写了，那么就可以按照继承类中函数调用， 强制性较纯虚稍微弱些
    //非纯虚函数 derived classes继承其函数接口，但impure virtual函数会提供一份实现代码，derived classes可能复写它。
    int objectID()const;//非虚函数 这种呢，你继承类中写了也不会覆盖它，相反基类会覆盖掉继承类中该函数
};
void Shape::draw()const
{
    cout<<"shape draw"<<endl;
}
void Shape::error(const std::string&msg)
{
    cout<<"shape error "<<endl;
}
Shape::Shape(){

}
int Shape::objectID()const//非虚函数
{
    cout<<"shape objectID"<<endl;
    return 0;
}
class Rectangle:public Shape{
public:
    Rectangle();
    void draw() const ;
    //void error(const std::string&msg);//非纯虚函数
};
Rectangle::Rectangle()
{

}
void Rectangle::draw()const
{

}
// void Rectangle::error(const std::string&msg)//非纯虚函数
// {
    
// }
class Ellipse:public Shape{
public:
    Ellipse();
    int objectID()const;//非虚函数
};
int Ellipse::objectID()const//非虚函数
{
    cout<<"Ellipse::objectID()"<<endl;
    return 0;
}
int main()
{
    //Shape *ps=new Shape;//Shape是抽象的
    Shape*ps1=new Rectangle;
    ps1->draw();
    ps1->error("ok");
    ps1->objectID();
    return 0;
}
/*
其接口表示，每个class都必须支持一个“当遇L错误时可调用＂的函数， 但
每个class可自由处理错误。 如果某个class不想针对错误做出任何特殊行为，
它可以退回到Shape class捉供的缺省错误处理行为。也就是说Shape: : error的声明式
“告诉derived classes的设计者，你必须支持一个error函数，但如果你不想自己写一个，可以使用Shapeclass提供的缺省版本” 。
*/





