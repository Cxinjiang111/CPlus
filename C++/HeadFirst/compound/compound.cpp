#include<iostream>
#include<string>
using namespace std;
//首先创建quackable接口
class Quackable
{
public:
    virtual void quack() = 0;
};
//某些鸭子实现了Quackable接口
//标准的绿头鸭
class MallardDuck:public Quackable
{
public:
    void quack()
    {
        cout << "标准绿头鸭MallardDuck quack" << endl;
    }
};
class RedheadDuck:public Quackable
{
public:
    void quack()
    {
        cout << "红鸭子 quack" << endl;
    }
};
//鸭鸣器，猎人使用的那种东西，他们肯定会呱呱叫）和橡皮鸭
class  DuckCall :public Quackable
{
public:
    void quack()
    {
        std::cout<<"猎人用的鸭子  kwak"<<std::endl;
    }
};
//橡皮鸭
class RubberDuck :public Quackable
{
public:
    void quack()
    {
        std::cout<<"橡皮鸭  Squeak"<<std::endl;
    }
};
class Goose
{
public:
    virtual void honk();
};
void Goose::honk(){std::cout<<"鹅 Honk"<<std::endl;}
class GooseAdapter : public Quackable
{
private:
    Goose *m_goose;
public:
    GooseAdapter(Goose *goose)
    {
        m_goose = goose;
    }
    void quack()override;
};
void GooseAdapter::quack()
{

    m_goose->honk();//看似象鸭子实际上是鹅
}
/*
要知道叫声的次数，让我们创建一个装饰者，通过包装进装饰者对象，给鸭子一些
新行为也就是计算次数的行为，

*/
//装饰者
//QuackCounter 

class QuackCounter :public Quackable
{
private:
    Quackable *m_duck;
public:
    static int m_numberOfQuacks;
    QuackCounter(Quackable *duck)
    {
        m_duck = duck;
    }
    void quack()
    {
        m_duck->quack();
        m_numberOfQuacks++;
    }
    static int getQuacks()
    {
        return m_numberOfQuacks;
    }
};
/*你必须通过装饰对象来获得被装饰过的行为，包装对象的问题就是这样，有包装才会有效果，没包装就没效果
我们需要一些质量控制来确保腰子一定是被包装起来的，我们要创建一个工厂，创建装饰过的鸭子，
*/
class AbstractDuckFactory
{
public:
    virtual Quackable* createMallardDuck() = 0;
    virtual Quackable* createRedheadDuck() = 0;
    virtual Quackable*createDuckCall() = 0;
    virtual Quackable* createRubberDuck() = 0;
};
class DuckFactory:public AbstractDuckFactory
{
public:
    Quackable* createMallardDuck()
    {
        return new MallardDuck();
    }
    Quackable* createRedheadDuck()
    {
        return new RedheadDuck();
    }    
    Quackable* createDuckCall()
    {
        return new DuckCall();
    }    
    Quackable* createRubberDuck()
    {
        return new RubberDuck();
    }    
};
//CountingDuckFactory也扩展自抽象工厂
//每个方法都会先用叫声计数装饰者将Quackable包装起来
//模拟器并不知道有何不同，只知道它实现了Quackable接口。
//但是巡逻员可以因此而放心，所有的叫声都会被计算进去
class CountingDuckFactory:public AbstractDuckFactory
{
public:
    Quackable* createMallardDuck()
    {
        return new QuackCounter(new MallardDuck());
    }
    Quackable* createRedheadDuck()
    {
        return new QuackCounter(new RedheadDuck());
    }
    Quackable* createDuckCall()
    {
        return new QuackCounter(new DuckCall());
    }
    Quackable* createRubberDuck()
    {
        return new QuackCounter(new RubberDuck());
    }
};
void simulate(Quackable * duck)
{
    duck->quack();
}
int QuackCounter::m_numberOfQuacks=0;
void simulate()
{
    
    AbstractDuckFactory *pabstractfactory=new CountingDuckFactory();
    //我们为什么要个别管理鸭子呢，我们需要将鸭子视为一个集合，甚至是自集合，为了满足巡逻员
    //想管理鸭子家族的要求，如果我们下一次命令，就能让整个集合的鸭子听命行事，那就太好了
    Quackable *pmallardDuckCount =pabstractfactory->createDuckCall();
    Quackable *pRedheadDuckCount =pabstractfactory->createRedheadDuck();
    Quackable *pDuckCallCount =pabstractfactory->createDuckCall();
    Quackable *pRubberDuckCount =pabstractfactory->createRubberDuck() ;

    std::cout<<"鸭子模拟器 simulator"<<std::endl;
    simulate(pmallardDuckCount);
    simulate(pRedheadDuckCount);
    simulate(pDuckCallCount);
    simulate(pRubberDuckCount);
    std::cout<<"Simulating count"<<QuackCounter::getQuacks()<<std::endl;
}
int main()
{
    simulate();
}





