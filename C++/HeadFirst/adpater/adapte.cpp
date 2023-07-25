#include<iostream>
#include<string>
using namespace std;
//鸭子
class Duck{
public:
    Duck();
    ~Duck();
    virtual void quack();
    virtual void fly();
};
Duck::Duck(){}
Duck::~Duck(){}
void Duck::quack(){std::cout<<"base Duck"<<std::endl;}
void Duck::fly(){std::cout<<"base fly"<<std::endl;}
//绿头鸭是有鸭子的子类
class MallardDuck: public Duck{
public:
    void quack();
    void fly();
};
void MallardDuck::quack()
{
    std::cout<<"MallardDuck quack"<<std::endl;
}
void MallardDuck::fly()
{
    std::cout<<"MallardDuck fly!"<<std::endl;
}
//火鸡
class Turkey{
public:
    virtual void gobble();
    virtual void fly();
};
void Turkey::gobble(){std::cout<<"base turkey  gobble"<<std::endl;}
void Turkey::fly()  {std::cout<<"base turkey  fly"<<std::endl;}
//-
class WildTurKey :public Turkey{
public:
    void gobble();
    void fly();
};
void WildTurKey::gobble(){std::cout<<"WildTurKey  gobble"<<std::endl;};
void WildTurKey::fly()   {std::cout<<"WildTurKey  fly   "<<std::endl;};
//假设你缺鸭子对象，想用一些火鸡来冒充，显然，因为火鸡的接口不同，所以我们不能公然拿来用
 //这里之所以要继承鸭子，你需要实现转换成的类型接口，也就是你的客户所期望看到的接口
class TurKeyAdapter:public Duck
{
private:
    Turkey *m_turkey;//这里之所以要组合，是因为要他的功能实现接口
public:
    TurKeyAdapter();
    ~TurKeyAdapter();
    //接着需要取得适配的对象引用，这里我们利用构造器取得这个引用
    TurKeyAdapter(Turkey *turkey);
    //quark() fly()鸭子的壳  实现火鸡的功能
    void quack(){
        std::cout << "TurKeyAdapter  quark "<< std::endl;
        m_turkey->gobble();
    }//
    void fly(){
        for(int i=0;i<5;++i)
            m_turkey->fly();
    }//
};
TurKeyAdapter::TurKeyAdapter(Turkey *turkey)
{
    m_turkey=std::move(turkey);
}
TurKeyAdapter::TurKeyAdapter(){}
TurKeyAdapter::~TurKeyAdapter(){}
int main()
{
    MallardDuck *pmallardduck=new MallardDuck();//鸭
    WildTurKey *pwildTurkey=new WildTurKey();//鸡
    Duck* pturKeyAdapter=new TurKeyAdapter(pwildTurkey);//申请的是鸭子类型，
    //功能是鸡的功能  quack  fly 是鸭子的属性 内部再去调用鸡的函数
    //适配的体现就是鸭子的接口，用来实现的鸡的功能
    pturKeyAdapter->quack();
    pturKeyAdapter->fly();
/*
TurKeyAdapter  quark 
WildTurKey  gobble
WildTurKey  fly   
WildTurKey  fly   
WildTurKey  fly   
WildTurKey  fly   
WildTurKey  fly   
*/
std::cout<<std::endl;
pmallardduck->quack();
pmallardduck->fly();
std::cout<<std::endl;
pwildTurkey->gobble();
pwildTurkey->fly();
    return 0;
}


