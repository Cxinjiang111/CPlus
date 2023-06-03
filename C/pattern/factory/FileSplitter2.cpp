#include<iostream>
/*
工厂方法模式的结构组成：
抽象工厂类厂（ShoesFactory）：工厂方法模式的核心类，提供创建具体产品的接口，由具体工厂类实现。
具体工厂类（NiKeProducer\AdidasProducer\LiNingProducer）：继承于抽象工厂，实现创建对应具体产品对象的方式。
抽象产品类（Shoes）：它是具体产品继承的父类（基类）。
具体产品类（NiKeShoes\AdidasShoes\LiNingShoes）：具体工厂所创建的对象，就是此类。
工厂方法模式的特点：
工厂方法模式抽象出了工厂类，提供创建具体产品的接口，交由子类去实现。
工厂方法模式的应用并不只是为了封装具体产品对象的创建，而是要把具体产品对象的创建放到具体工厂类实现。
工厂方法模式的缺陷：
每新增一个产品，就需要增加一个对应的产品的具体工厂类。相比简单工厂模式而言，工厂方法模式需要更多的类定义。
一条生产线只能一个产品。
工厂方法模式的代码：
ShoesFactory抽象工厂类，提供了创建具体鞋子产品的纯虚函数。
NiKeProducer、AdidasProducer、LiNingProducer具体工厂类，继承持续工厂类，实现对应具体鞋子产品对象的创建。
*/
//--------------抽象鞋子类----------
class Shoes{
public:
    virtual void show()=0;
    virtual ~Shoes(){}
};
//具体实现类
class NikeShoes:public Shoes{
public :
    void show(){
        std::cout<<"NIKe shoes"<<std::endl;
    }
};
//----------鞋子的具体功能实现类------
class AdidasShoes:public Shoes{
public :
    void show(){
        std::cout<<"NIKe shoes"<<std::endl;
    }
};
class LiNingShoes:public Shoes{
public :
    void show(){
        std::cout<<"NIKe shoes"<<std::endl;
    }
};
//-----------工厂基类------------
class ShoesFactory{
public:
    virtual Shoes*CreateShoes()=0;
    virtual ~ShoesFactory(){}
};
//-----------工厂生产链创建对象-----------
class NiKeProducer:public ShoesFactory{
public:
    Shoes *CreateShoes()
    {
        return new NikeShoes();
    }
};
class LiNingProducer :public ShoesFactory{
public:
    Shoes *CreateShoes()
    {
        return new  LiNingShoes();
    }
};
class AdidasProduce:public ShoesFactory{
public:
    Shoes *CreateShoes()
    {
        return new AdidasShoes();
    }
};
int main(){
     // ================ 生产耐克流程 ==================== //
    // 基类                             父类
    ShoesFactory *nikeProducer=new NiKeProducer();//创建抽象工厂对象，以便访问
    Shoes *nikeShoes=nikeProducer->CreateShoes();//利用抽象工厂访问创建的对象
    nikeShoes->show();
    delete nikeProducer;
    delete nikeShoes;
     // ================ 生产耐克流程 ==================== //
    // 基类                             父类
    ShoesFactory *liningProducer=new LiNingProducer();//创建抽象工厂对象，以便访问
    Shoes *liningShoes=liningProducer->CreateShoes();//利用抽象工厂访问创建的对象
    liningShoes->show();
    delete liningProducer;
    delete liningShoes;
     // ================ 生产耐克流程 ==================== //
    // 基类                             父类
    ShoesFactory *adidasProduce=new AdidasProduce();//创建抽象工厂对象，以便访问
    Shoes *adidasShoes=adidasProduce->CreateShoes();//利用抽象工厂访问创建的对象
    adidasShoes->show();
    delete adidasProduce;
    delete adidasShoes;

}
