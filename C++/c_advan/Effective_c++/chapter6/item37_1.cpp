#include<iostream>
// class Shape{
// public:
//     enum ShapeColor{Red,Green,Blue};
//     virtual void draw(ShapeColor color=Red)const=0;
// };
// class Rectangle:public Shape{
// public:
//     virtual void draw(ShapeColor color=Red)const;
// };
/*
喔欧， 代码重复。 更糟的是， 代码重复又带着相依性(with dependencies) 
如果Shape内的缺省参数值改变了， 所有 “重复给定缺省参数值 ” 的那些derived classes也必须改变，
否则它们最终会导致 “ 重复定义一个继承而来的缺省参数值“ 。 怎么办？

当你想令virtual函数表现出你所想要的行为但却遭遇麻烦，聪明的做法是考虑替代设计。
条款35列了不少virtual函数的替代设计，其中之一是NVI (non-virtual interface)手法：
令base class内的 一个public non-virtual函数调用private virtual函 数， 
后者可被derived classes重新定义。 这里我们可以让non-virtual函数指定缺省 
参数， 而private virtual函数负责真正的工作：
*/
class Shape{
public:
    enum ShapeColor{Red,Green,Blue};
    void draw(ShapeColor color=Red)const{
        dodraw(color);
    }
private:
    virtual void dodraw(ShapeColor color)const=0;
};
class Rectangle:public Shape{
public:
private:
    virtual void dodraw(ShapeColor color)const;
};
void Rectangle::dodraw(ShapeColor color)const
{
    std::cout<<color<<std::endl;
}
int main()
{
    Rectangle r;
    r.draw(Shape::Blue);

    return 0;
}

