/*绝不重新定义继承而来的缺省参数值
绝对不要重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定， 而virtual函数一一你唯一应该覆写的东西——却是动态绑定。
*/
/*
让我们一开始就将讨论简化。你只能继承两种函数：virtual和non-virtual函数。
然而重新定义一个继承而来的non-virtual函数永远是错误的（见条款36)，
所以我 们可以安全地将本条款的讨论局限千 “ 继承一个带有缺省参数值的virtual函数” 。
这种情况下，本条款成立的理由就非常直接而明确了：virtual函数系动态绑定(dynamically bound)，
而缺省参数值却是静态绑定(staticallybound)。
*/
#include<iostream>
using namespace std;
class Shape{
public:
    enum ShapeColor{Red,Green,Blue};
    virtual void draw(ShapeColor color=Red)const=0;
};
class Rectangle:public Shape{
public:
    //注意 赋予不同的缺省参数值 真糟糕
    virtual void draw(ShapeColor color=Green)const; //error 
};
void Rectangle::draw(ShapeColor color=Green)const
{

}
class Circle:public Shape{
public:
//请注意，以上这么写则当客户以对象调用此函数，一定要指定参数值
/*
因为静态绑定下这个函数并不从其base继承缺省参数值。 
但若以指针（或reference)调用此函数， 可以不指定参数值， 
因为动态绑定下这个函数会从其base继承缺省参数值。
*/
    virtual void draw(ShapeColor color)const; 
};
void Circle::draw(ShapeColor color)const
{
    cout<<"Circle::draw"<<color<<endl;
}
int main()
{
    Shape::ShapeColor col=Shape::Blue;
    Circle c;
    c.draw(col);//output 2 Blue 
    // Rectangle r;//error
    // r.draw(col);


    return 0;
}
/*
为什么 C+＋坚持以这种乖张的方式来运作呢？答案在千运行期效率。
如果缺省参数值 是动态绑定，编译器就必须有某种办法在运行期为virtual函数决定适当的
参数缺省值。这比目前实行的 “在编译期决定”的机制更慢而且更复杂。
为了程序的执行速度和编译器实现上的简易度，C++ 做了这样的取舍，
其结果就是你如今所享受的执行效率。但如果你没有注意本条款所揭示的忠告，很容易发生混淆。

*/


