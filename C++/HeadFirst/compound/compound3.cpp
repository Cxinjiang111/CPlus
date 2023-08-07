#include<iostream>
#include<string>
#include<list>
using namespace std;
class QuackObservable;
//感觉程序实现还没有完
//首先创建quackable接口 实现功能性类
//观察者模式 跟踪鸭子的行为
class Observer
{
public:
    Observer();
    virtual ~Observer();
    virtual void update(QuackObservable *quckobservable);
};
Observer::Observer(){}
Observer::~Observer(){}
void Observer::update(QuackObservable *quckobservable){}
//我们需要实现Observable接口，否则就无法以QuackObservable注册
class Quacklogist:public Observer
{

public:
    Quacklogist(){}
    ~Quacklogist(){}
    void update(QuackObservable *quackobservable)
    {
        std::cout << "Quacklogist "<< std::endl;
    }
};
//任何想被观察的Quackable都必须实现QuackObservable的接口
class QuackObservable
{
public:
    //它具有注册观察者的方法，任何实现了Observer接口的对象都可以监控呱呱叫，
    void registerObserver(Observer* observer);
    void notifyObservers();//他也有通知通知观察者的方法
};
//这里采用继承与组合了QuackObservable
/*
Observerble实现了所有必要的功能，我们只要把他插进一个类，就可以让该类将工作委托给Observerble
Observerble必须实现QuackObservable，因为它们具有一组相同的方法，QuackObservable会将这些方法
的调用转给Observable的方法，
*/
class Observerble:public QuackObservable
{
private:
    list<Observer*> m_observers;
    QuackObservable *m_duck;
public:
//在此构造器中，我们传进QuackObservable，看看下面的notify方法，你会发现当通知时
//观察者把此对象传过去，好让观察者知道时哪个对象在呱呱叫
    Observerble(QuackObservable *duck) : m_duck(duck){}
    void registerObserver(Observer* observer)
    {
        m_observers.push_back(observer);
    }
    void notifyObservers()//只是通知用的代码
    {
        for(auto it=m_observers.begin();it!=m_observers.end();++it)
        {
            (*it)->update(m_duck);
        }
    }
};
class Quackable:public QuackObservable
{
public:
    virtual void quack() = 0;
    void registerObserver(Observer* observer);
    void notifyObservers();//他也有通知通知观察者的方法    
};
void Quackable::registerObserver(Observer* observer){}
void Quackable::notifyObservers(){}//他也有通知通知观察者的方法  
//某些鸭子实现了Quackable接口
//标准的绿头鸭
class MallardDuck:public Quackable
{
private:
    Observerble *m_observable;
public:
    MallardDuck(){ m_observable = new Observerble(this);}
    void quack()
    {
        cout << "标准绿头鸭MallardDuck quack" << endl;
        notifyObservers();
    }
    void registerObservers(Observer *observer){m_observable->registerObserver(observer);}
    void notifyObservers()
    {
        m_observable->notifyObservers();
    }
};
class RedheadDuck:public Quackable
{
private:
    Observerble *m_observable;
public:
    void quack()
    {
        cout << "红鸭子 quack" << endl;
    }
    void registerObservers(Observer *observer){m_observable->registerObserver(observer);}
    void notifyObservers()
    {
        m_observable->notifyObservers();
    }
};
//鸭鸣器，猎人使用的那种东西，他们肯定会呱呱叫）和橡皮鸭
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
//我们也需要跟踪个别的鸭子，你能够有办法让我持续跟踪个别鸭子的呱呱叫
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
void simulateFactory()
{
    Flock *pFlock=new Flock();
    //添加动物数量
    pFlock->add(new MallardDuck());
    pFlock->add(new RedheadDuck());
    Observer *pquacklogist = new Quacklogist();
   //添加观察者
    pFlock->registerObserver(pquacklogist);
    //执行
    pFlock->quack();
}
int main()
{
    simulateFactory();
}