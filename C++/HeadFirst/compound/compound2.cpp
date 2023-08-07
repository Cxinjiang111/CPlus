#include<iostream>
#include<string>
#include<list>
using namespace std;
//首先创建quackable接口 实现功能性类
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
你必须通过装饰对象来获得被装饰过的行为，包装对象的问题就是这样，有包装才会有效果，没包装就没效果
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
void simulate(Quackable * duck)
{
    duck->quack();
}
int QuackCounter::m_numberOfQuacks=0;
//问题？？？？
//我们为什么要个别管理鸭子呢，我们需要将鸭子视为一个集合，甚至是自集合，为了满足巡逻员
//想管理鸭子家族的要求，如果我们下一次命令，就能让整个集合的鸭子听命行事，那就太好了
/*
void simulate()
{
    //对于一下代码感觉依然不好管理，或者添加一个依然麻烦
    Quackable *pmallardDuck=new MallardDuck();
    Quackable *pRedheadDuck= new RedheadDuck();
    Quackable *pDuckCall= new DuckCall();
    Quackable *pRubberDuck= new RubberDuck();
    Goose *pgoose=new Goose();
    //鹅目前也会呱呱叫了
    Quackable *pgooseadapter= new GooseAdapter(pgoose);
    //========= 

    Quackable *pmallardDuckCount =new QuackCounter(pmallardDuck);
    Quackable *pRedheadDuckCount =new QuackCounter(pRedheadDuck);
    Quackable *pDuckCallCount =new QuackCounter(pDuckCall);
    Quackable *pRubberDuckCount =new QuackCounter(pRubberDuck);
    //Quackable *pgooseadapterCount =new QuackCounter(pgooseadapter);//不统计鹅的叫声，所有不必去装饰鹅

    std::cout<<"鸭子模拟器 simulator"<<std::endl;
    simulate(pmallardDuckCount);
    simulate(pRedheadDuckCount);
    simulate(pDuckCallCount);
    simulate(pRubberDuckCount);
    simulate(pgooseadapter);
    std::cout<<"Simulating count"<<QuackCounter::getQuacks()<<std::endl;
}
*/
class Flock:public Quackable 
{
private:
    list<Quackable*> m_quackes;//这里采用链表 迭代器模型
public:
    void add(Quackable* quack){m_quackes.push_back(quack);}
    void quack()
    {
        for(auto i=m_quackes.begin();i!=m_quackes.end();++i)
        {
            (*i)->quack();
        }
    }
};
void simulate()
{
    //对于一下代码感觉依然不好管理，或者添加一个依然麻烦
    Quackable *pmallardDuck=new MallardDuck();
    Quackable *pRedheadDuck= new RedheadDuck();
    Quackable *pDuckCall= new DuckCall();
    Quackable *pRubberDuck= new RubberDuck();
    Goose *pgoose=new Goose();
    //鹅目前也会呱呱叫了
    Quackable *pgooseadapter= new GooseAdapter(pgoose);
    //========= 
    Flock *pFlock=new Flock();
    pFlock->add(pmallardDuck);
    pFlock->add(pRedheadDuck);
    pFlock->add(pDuckCall);
    pFlock->add(pRubberDuck);
    pFlock->quack();
}

int main()
{
    simulate();
}