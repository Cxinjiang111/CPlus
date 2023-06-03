#include<iostream>
using namespace std;
/*
中介者模式：用一个中介对象来封装一系列的对象交互，
中介者使各对象不需要显示地相互引用，从而使其耦合松散，
而且可以独立地改变它们之前的交互。

如果对象与对象之前存在大量的关联关系，若一个对象改变，
常常需要跟踪与之关联的对象，并做出相应的处理，这样势必会造成系统变得复杂，
遇到这种情形可以考虑使用中介者模式。当多个对象存在关联关系时，
为它们设计一个中介对象，当一个对象改变时，只需要通知它的中介对象，
再由它的中介对象通知每个与它相关的对象。
*/
class Mediator;
//相当于还是一个基类 抽象同事类
class Businessman{ 
public:
    Businessman(){}
    Businessman(Mediator*mediator):m_pMediator(mediator){}
    ~Businessman(){}
    virtual  void setMediator(Mediator *m){
        m_pMediator=m;
    }
    virtual void sendMessage(const string &msg)=0;
    virtual void getMessage(const string &msg)=0;

protected:
    Mediator *m_pMediator;//组合
};
//抽象中介者类
class Mediator{
public:
    virtual ~Mediator(){}
    virtual void setBuyer(Businessman *buyer)=0;
    virtual void setSeller(Businessman*seller)=0;
    virtual void send(const string &msg,Businessman*man)=0;
};
class Buyer:public Businessman{
public:
    Buyer():Businessman(){}
    Buyer(Mediator*mediator):Businessman(mediator){}
    void sendMessage(const string &msg){
        m_pMediator->send(msg,this);
        cout<<"Buyer sendMessage"<<endl;
    }
    void getMessage(const string &msg){
        cout<<"Buyer getMessage:"<<msg.data()<<endl;
    }
};

class Seller:public Businessman{
public:
    Seller():Businessman(){}
    Seller(Mediator *mediator):Businessman(mediator){}

    void sendMessage(const string &msg){
        m_pMediator->send(msg,this);
        cout<<"Seller sendMessage"<<endl;
    }
    void getMessage(const string &msg){
        cout<<"seller recv:"<<msg.data()<<endl;
        cout<<"Seller getMessage"<<endl;
    }
};
//继承Mediator的虚函数
class HouseMediator:public Mediator{
public:
    void setBuyer(Businessman*buyer){
        cout<<"HouseMediator setBuyer"<<endl;
        m_pBuyer=buyer;
    }
    void setSeller(Businessman*seller){
        cout<<"HouseMediator setSeller"<<endl;
        m_pSeller=seller;
    }
    void send(const string &msg,Businessman*man){
        if(man==m_pBuyer){
            m_pSeller->getMessage(msg);
        }
        else if(man==m_pSeller){
            m_pBuyer->getMessage(msg);
        }
     }
private:
    Businessman *m_pBuyer;//组合
    Businessman *m_pSeller;
};
int main(){
    HouseMediator *hMediator=new HouseMediator;
    //HouseMediator内存结构中含有Businessman的内存对象
    //Buyer Seller继承Businessman那么Buyer Seller中一定含有Businessman的内存结构
    Buyer*buyer=new Buyer(hMediator);
    Seller *seller=new Seller(hMediator);

    hMediator->setBuyer(buyer);
    hMediator->setSeller(seller);
    buyer->sendMessage("sell not to sell?");
    seller->sendMessage("of couse selling");
 
    delete buyer;
    buyer = nullptr;
    delete seller;
    seller = nullptr;
    delete hMediator;
    hMediator = nullptr;
    return 0;
}

