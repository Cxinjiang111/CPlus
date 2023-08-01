 #include<iostream>
 using namespace std;
class GumballMachine
{
private:
    int SOLD_OUT=0;
    int NO_QUARETER=1;
    int HAS_QUARETER=2;
    int SOLD=3;
    int m_state=SOLD_OUT;//跟踪当前状态
    int m_count=0;//跟踪当前机器的糖果数目
public:
    GumballMachine(int count){
        m_count=count;
        if(count>0)
            m_state=NO_QUARETER;// 有糖果 没有钱
    }
    int getState(){return m_count;}
    //向里面投钱25
    void insertQuarter()
    {//处理每种状态对应需要处理的事情
        if(m_state==SOLD_OUT)
        {
            std::cout << "已售完的状态，你不能再投钱了"<<std::endl;
        }
        else if(m_state==NO_QUARETER)
        {
            m_state=HAS_QUARETER;//在没投钱时投钱了 就变成了有钱
            std::cout << "没有钱的状态"<<std::endl;
        }
        else if(m_state==HAS_QUARETER)
        {
            std::cout << "已经投过钱了 不能在投钱了"<<std::endl;
        }
        else if(m_state==SOLD)
        {
            std::cout<<" 正在扭动曲柄，正在售出 "<<std::endl;
        }
    }
    //如果顾客尝试着退回25分钱
    void ejectQuarter()
    {
        if(m_state==HAS_QUARETER)
        {
            std::cout<<" 可以退出25分钱"<<std::endl;
            m_state=NO_QUARETER;
        }
        else if(m_state==NO_QUARETER)
        {
            std::cout<<" 里面没有钱，不能退钱"<<std::endl;
        }
        else if(m_state==SOLD)
        {
            std::cout<<" 对不起，你已经 扭转过曲柄，不能在拿钱了"<<std::endl;
        }
        else if(m_state==SOLD_OUT)
        {
            std::cout<<"你不能退回 你还没有投入过钱"<<std::endl;
        }
    }
    //如果顾客尝试扭转曲柄
    void turnCrank()
    {
        if(m_state==SOLD)
        {
            std::cout<<" 你已经扭转过曲柄，不能再拿糖果了"<<std::endl;
        }
        else if(m_state==SOLD_OUT)
        {
            std::cout<<"不能在给糖果了，没有任何糖果了 "<<std::endl;
        }
        else if(m_state==NO_QUARETER)
        {
            std::cout<<"我们需要先投25分钱"<<std::endl;
        }
        else if(m_state==HAS_QUARETER)
        {
            std::cout<<"成功拿到糖果了"<<std::endl;
            m_state=SOLD;
            dispense();
        }
    }
    //发放糖果
    void dispense()
    {
        if(m_state==SOLD)
        {
            std::cout<<" 正在售出糖果，给他们糖果"<<std::endl;
            m_count=m_count-1;
            if(m_count==0)
            {
                std::cout<<" 现在没有糖果了"<<std::endl;
                m_state=SOLD_OUT;//最后一颗糖果卖没了，
            }
            else{
                m_state=NO_QUARETER;//还有糖果，回到没有25分钱的状态。
            }
        }
        else if(m_state==NO_QUARETER)
        {
            std::cout<<"你需要 先付钱"<<std::endl;
        }
        else if(m_state==SOLD_OUT)
        {
            std::cout<<"没有糖果可以发了"<<std::endl;
        }
        else if(HAS_QUARETER)
        {
            std::cout<<"没有糖果可以发了"<<std::endl;
        }
    }
};
int main()
{
    GumballMachine *pgumballmachine = new GumballMachine(5);
    std::cout<<pgumballmachine->getState()<<std::endl;
    pgumballmachine->insertQuarter();//投入25分钱
    pgumballmachine->turnCrank();
    std::cout<<pgumballmachine->getState()<<std::endl;
    std::cout<<"================"<<std::endl;//4
    pgumballmachine->insertQuarter();
    pgumballmachine->ejectQuarter();
    pgumballmachine->turnCrank();
    std::cout<<pgumballmachine->getState()<<std::endl;
    std::cout<<"================"<<std::endl;//4

    pgumballmachine->insertQuarter();
    pgumballmachine->turnCrank();
    pgumballmachine->insertQuarter();
    pgumballmachine->turnCrank();
    pgumballmachine->ejectQuarter();

    std::cout<<pgumballmachine->getState()<<std::endl;//2
    std::cout<<"================"<<std::endl;

    pgumballmachine->insertQuarter();
    pgumballmachine->insertQuarter();
    pgumballmachine->turnCrank();
    pgumballmachine->insertQuarter();
    pgumballmachine->turnCrank();
    pgumballmachine->insertQuarter();
    pgumballmachine->turnCrank();
    std::cout<<pgumballmachine->getState()<<std::endl;
    return 0;
}