/*确定你的public继承塑膜出is-a关系
public继承“ 意味比a。 适用千base classes身上的每一件事情一定也适用千 derived classes身上，
因为每一个derivedclass对象也都是一个baseclass对象。
*/
/*
如果你令classD ("Derived”)以public形式继承classB ("Base")，你便是告 
诉C++编译器（以及你的代码读者）说，每一个类型为D的对象同时也是一个类型为B的对象， 反之不成立。 
你的意思是B比o表现出更一般化的概念， 而D比B表现出更特殊化的概念。 你主张 “B对象可派上用场的任何地方，
D对象一样可以派上用场 ” （译注：此即所谓Liskov Substitution Principle)， 因为每一个D对象都
一是种（是一个）B对象。 反之如果你需要一个D对象，B对象无法效劳， 因为虽然每个D对象都是 个B对象， 
反之不成立
*/
class Person{
};
class Student:public Person{
};
void eat(const Person&p);
void study(const Student&s);
void f()
{
    Person p;
    Student s;
    eat(p);
    eat(s);
    study(s);
    //study(p);//error 
}
/*
这个论点只对public继承才成立。 只有当Student以public形式继承Person,
C+＋的行为才会如我所描述。private继承的意义与此完全不同（见条款39)， 至于
protected继承， 那是一种其意义至今仍然困惑我的东西。

public继承和is-a之间的等价关系听起来颇为简单， 但有时候你的直觉可能会
误导你。举个例子，企鹅(penguin)是一种鸟，这是事实。 鸟可以飞，这也是事实。
如果我们天真地以C丑描述这层关系， 结果如下：
*/
class Bird{
public:
    virtual void fly();//所有鸟可以飞
};
class Penguin:public Bird{ //企鹅是一种鸟 但不能非，上面的基类的fly是要求必须继承的 所以有问题

};
//----------
class Bird{
        //fly()没有此函数的申明
};
class FlyingBird:public Bird{
public:
    virtual void fly();
};
class Penguin:public Bird{
                        //这里不申明fiy函数
};
/*
即便如此，此刻我们仍然未能完全处理好这些鸟事，因为对某些软件系统而言，可能不需要区分会飞的鸟和不会飞的鸟。
如果你的程序忙着处理鸟喙和鸟翅，完全不在乎飞行，原先的“双classes继承体系”或许就相当令人满足了。
这反映出一个事实，世界上并不存在一个“适用千所有软件”的完美设计。所谓最佳设计，取决于系统希望做什么事，
包括现在与未来。如果你的程序对飞行一无所知，而且也不打算未来对飞行 “有所知”，那么不去区分会飞的鸟和不会飞的鸟，
不失为一个完 美而有效的设计。实际上它可能比“对两者做出区隔” 更受欢迎，因为这样的区隔 在你企图塑模的世界中并不存在。
*/



