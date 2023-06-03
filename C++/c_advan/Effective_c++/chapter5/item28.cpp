/*避免返回handles指向对象内部成分
避免返回handles（包括references、 指针、 迭代器）指向对象内部 。遵守这个条 款可增加封装性，
 帮助const成员函数 的行为像个const, 并将发生 “虚吊号码 ”牌 (dangling handles) 的可能性降至最低。

*/
#include<memory>
class Point{
public:
    Point(int x_,int y_);
    void setX(int newval);
    void setY(int newval);
private:
    int x,y;
};
struct RectData{
    Point ulhc;
    Point lrhc;
};
class Rectangle{
    Point&upperLeft()const {return pData->lrhc;}//调用者能够使用被返回的reference来更改成员,但rec其实应该时不可变的
    Point&lowerRight()const {return pData->ulhc;}  
    //Rectangle(Point&  p1,Point &p2):pData.ulhc(p1){}; ??error
private:
    std::shared_ptr<RectData> pData;//4字节指针，降低了Rectangle结构体大小
};
int main()
{
    Point p1(0,1);
    Point p2(10,10);
    const Rectangle rec(p1,p2);//error 
    rec.upperLeft().setX(50);
}
/*
这立刻带给我们两个教训。 第一，成员变量的封装性最多只等千 “返回 其 reference"的函数的访问级别。
 本例之中虽然ulhc和lrhc都被声明为private, 它们实际上却是public,因为public函数
  upperLeft和lowerRight传出了它们的references。第二，如果const成员函数传出一个reference,
  \后者所指数据与对象自身有关联， 而它又被存储千对象之外，那么这个函数的调用者可以修改那笔数据。
这正是bitwise constness的一个附带结果，见条款3。

上面我们所说的每件事情都是由千 ” 成员函数返回references"。如果它们返 回的是指针或迭代器，
相同的情况还是发生，原因也相同。 References、 指针和迭 代器统统都是所谓的handles（号码牌，用来取得某个对象），
而返回 代表对象内部数据 ＂ 的handle,随之而来的便是 “ 降低对象封装性” 的风险。 同时，一
如稍早所见，它也可能导致 “虽然调用const成员函数却造成对象状态被更改” 。

通常我们认为，对象的“ 内部 ” 就是指它的成员变量，但其实不被公开使用的 成员函数
（也就是被声明为protected或private者）也是对象 “ 内部” 的一部分。 因此也应该留心不要返回它们的handles。
这意味你绝对不该令成员函数返回一个指针指向 “访问级别较低＂ 的成员函数。 如果你那么做，
后者的实际访问级别就会提高如同前者（访问级别较高者），因为客户可以取得一个指针指向那个 “访问级别
 较低＂ 的函数，然后通过那个指针调用它。

然而“返回指针指向某个成员函数”的情况毕竟不多见，所以让我们把注意力收回，
专注于Rectangleclass和它的upperLeft以及lowerRight成员函数。我们 在这些函数身上遭遇的两个问题可以轻松去除，
只要对它们的返回类型加上const 即可：

*/
class Rectangle{
    const Point&upperLeft()const {return pData->lrhc;}//调用者能够使用被返回的reference来更改成员,但rec其实应该时不可变的
    const Point&lowerRight()const {return pData->ulhc;}  
    //Rectangle(Point&  p1,Point &p2):pData.ulhc(p1){}; ??error
private:
    std::shared_ptr<RectData> pData;//4字节指针，降低了Rectangle结构体大小
};
/*
有了这样的改变，客户可以读取矩形的Points,但不能涂写它们。这意味当初 声明upper Left和upperRight为const不再是个谎言，
因为它们不再允许客户更 改对象状态。 至千封装问题，我们总是愿意让客户看到Rectangle的外围Points, 所以这里是蓄意放松封装。
更重要的是这是个有限度的放松：这些函数只让渡读取 权。 涂写权仍然是被禁止的。

*/

