#include<iostream>
using namespace std;
//这个代码存在类相互包含的问题，导致无法编译
class GumballMachine;
class State;

class State
{
public:
    State();
    virtual ~State();
    //向里面投钱25
    virtual void insertQuarter();
    //如果顾客尝试着退回25分钱
    virtual void ejectQuarter();
    //如果顾客尝试扭转曲柄
    virtual void turnCrank();
    //发放糖果
    virtual void dispense();
};
State::State(){}
State::~State(){}
//向里面投钱25
void State::insertQuarter(){}
//如果顾客尝试着退回25分钱
void State::ejectQuarter(){}
//如果顾客尝试扭转曲柄
void State::turnCrank(){}
//发放糖果
void State::dispense(){}
class Gumball
{
public:
    Gumball(){}
    ~Gumball(){}
    virtual void setState(State *state);
    virtual State *getsoldOutState();
    virtual State *getnoQuarterState();
    virtual State *hasQuarterState();
    virtual State *getsoldState();
    virtual int getCount();
    virtual int setCount(int count);
};
void Gumball::setState(State *state){}
State *Gumball::getsoldOutState(){}
State *Gumball::getnoQuarterState(){}
State *Gumball::hasQuarterState(){}
State *Gumball::getsoldState(){}
int Gumball::getCount(){}
int Gumball::setCount(int count){}
class NoQuarterState: public State
{
private:
    Gumball *m_gumballMachine;
public:
    NoQuarterState(Gumball *gumballMachine):m_gumballMachine(gumballMachine){}
    NoQuarterState(){};
    ~NoQuarterState(){};
    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    void dispense(); 
};
void NoQuarterState::insertQuarter()
{
    m_gumballMachine->setState(m_gumballMachine->hasQuarterState());//在没投钱时投钱了 就变成了有钱
    std::cout << "没有钱的状态"<<std::endl;
}
//如果顾客尝试着退回25分钱
void NoQuarterState::ejectQuarter()
{
    std::cout<<" 里面没有钱，不能退钱"<<std::endl;
}
//如果顾客尝试扭转曲柄
void NoQuarterState::turnCrank()
{
    std::cout<<"我们需要先投25分钱"<<std::endl;
}
//发放糖果
void NoQuarterState::dispense()
{
    std::cout<<"你需要 先付钱"<<std::endl;
}
class HasQuarterState: public State
{
private:
Gumball *m_gumballMachine;
public:
    HasQuarterState();
    HasQuarterState(Gumball *gumballMachine):m_gumballMachine(gumballMachine){}
    ~HasQuarterState();
    void insertQuarter();
    //如果顾客尝试着退回25分钱
    void ejectQuarter();
    //如果顾客尝试扭转曲柄
    void turnCrank();
    //发放糖果
    void dispense(); 
};
HasQuarterState::HasQuarterState(){}
HasQuarterState::~HasQuarterState(){}
void HasQuarterState::insertQuarter()
{
    std::cout << "已经投过钱了 不能在投钱了"<<std::endl;
}
//如果顾客尝试着退回25分钱
void HasQuarterState::ejectQuarter()
{
    std::cout<<" 可以退出25分钱"<<std::endl;
}
//如果顾客尝试扭转曲柄
void HasQuarterState::turnCrank()
{
    std::cout<<"成功拿到糖果了"<<std::endl;
    m_gumballMachine->setState(m_gumballMachine->getsoldState());
    dispense();
}
//发放糖果
void HasQuarterState::dispense()
{
    std::cout<<"没有糖果可以发了"<<std::endl;
}
class SoldState: public State
{
private:
Gumball *m_gumballMachine;
public:
    SoldState(Gumball *gumballMachine):m_gumballMachine(gumballMachine){};
    SoldState();
    ~SoldState();
    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    void dispense(); 
};
SoldState::SoldState(){}
SoldState::~SoldState(){}
void SoldState::insertQuarter()
{
    std::cout<<" 正在扭动曲柄，正在售出 "<<std::endl;
}
//如果顾客尝试着退回25分钱
void SoldState::ejectQuarter()
{
    std::cout<<" 对不起，你已经 扭转过曲柄，不能在拿钱了"<<std::endl;
}
//如果顾客尝试扭转曲柄
void SoldState::turnCrank()
{
    std::cout<<" 你已经扭转过曲柄，不能再拿糖果了"<<std::endl;
}
//发放糖果
void SoldState::dispense()
{
    std::cout<<" 正在售出糖果，给他们糖果"<<std::endl;
    m_gumballMachine->setCount(m_gumballMachine->getCount()-1);
    if(m_gumballMachine->getCount()==0)
    {
        std::cout<<" 现在没有糖果了"<<std::endl;
        m_gumballMachine->setState(m_gumballMachine->getsoldOutState());//最后一颗糖果卖没了，
    }
    else{
        std::cout<<"没有糖了"<<std::endl;
        m_gumballMachine->setState(m_gumballMachine->getnoQuarterState());//还有糖果，回到没有25分钱的状态。
    }
}
class SoldOutState: public State
{
private:
    Gumball *m_gumballMachine;
public:
    SoldOutState(Gumball *gumballMachine):m_gumballMachine(gumballMachine){};
    SoldOutState();
    ~SoldOutState();
    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    void dispense(); 
};
SoldOutState::SoldOutState(){}
SoldOutState::~SoldOutState(){}
void SoldOutState::insertQuarter()
{
    std::cout << "已售完的状态，你不能再投钱了"<<std::endl;
}
//如果顾客尝试着退回25分钱
void SoldOutState::ejectQuarter()
{
    std::cout<<"你不能退回 你还没有投入过钱"<<std::endl;
}
//如果顾客尝试扭转曲柄
void SoldOutState::turnCrank()
{
    std::cout<<"不能在给糖果了，没有任何糖果了 "<<std::endl;
}
//发放糖果
void SoldOutState::dispense()
{
    std::cout<<"没有糖果可以发了"<<std::endl;
}

class GumballMachine:public Gumball
{
private:
    State *m_soldOutState=nullptr;//
    State *m_noQuarterState=nullptr;//
    State *m_hasQuarterState=nullptr;//
    State *m_soldState=nullptr;//
    State *m_state=nullptr;//当前状态
    int m_count=0;//糖果数目
    string m_location;//记录位置
public:
    GumballMachine(string location,int numberGumballs){
        m_soldOutState=new SoldOutState();
        m_noQuarterState=new NoQuarterState();
        m_hasQuarterState=new HasQuarterState();
        m_soldState=new SoldState();
        m_state=m_soldState;
        m_count=numberGumballs;//
        m_location=location;
    }
    void insertQuarter()
    {
        m_state->insertQuarter();
    }
    //如果顾客尝试着退回25分钱
    void ejectQuarter()
    {
        m_state->ejectQuarter();
    }
    //如果顾客尝试扭转曲柄
    void turnCrank()
    {
        m_state->turnCrank();
        m_state->dispense();
    }
    //发放糖果
    void dispense()
    {
    }
    string getLocation(){return m_location;}
    void setState(State *state){ m_state=state;}
    State *getsoldOutState()  {return m_soldOutState;}
    State *getnoQuarterState(){return m_noQuarterState;}
    State *hasQuarterState()  {return m_hasQuarterState;}
    State *getsoldState()     {return m_soldState;}    
    int getCount(){return m_count;}
    int setCount(int count){m_count=count;}        
    void releaseBall()
    {
        std::cout<<" "<<std::endl;
        if(m_count>0)
        {
            m_count=m_count-1;
        }  
    }
};
//糖果监视器，以便取得机器的位置，糖果的库存量以及当前机器的状态，并打印报告
class GumballMonitor
{
private:
    GumballMachine* m_machine;
public:
    //传入机器的信息
    GumballMonitor(GumballMachine *machine) : m_machine(machine){}
    //打印机器的所有信息
    void report()
    {
        std::cout<<"Gumball Machine: "<<m_machine->getLocation()<<std::endl;
        std::cout<<"current inventory: "<<m_machine->getCount()<<std::endl;
    }


};
