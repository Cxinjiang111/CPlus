#include<iostream>
/*
 ---抽象工厂模式-----
抽象工厂类厂（ShoesFactory）：工厂方法模式的核心类，提供创建具体产品的接口，由具体工厂类实现。
具体工厂类（NiKeProducer）：继承于抽象工厂，实现创建对应具体产品对象的方式。
抽象产品类（Shoes\Clothe）：它是具体产品继承的父类（基类）。
具体产品类（NiKeShoes\NiKeClothe）：具体工厂所创建的对象，就是此类。
抽象工厂模式的特点：
提供一个接口，可以创建多个产品族中的产品对象。如创建耐克工厂，则可以创建耐克鞋子产品、衣服产品、裤子产品等。
抽象工厂模式的缺陷：
同工厂方法模式一样，新增产品时，都需要增加一个对应的产品的具体工厂类。
抽象工厂摸是的代码：
Clothe和Shoes，分别为衣服和鞋子的抽象产品类。
NiKeClothe和NiKeShoes，分别是耐克衣服和耐克衣服的具体产品类。
*/
class Clothe{
public:
    virtual void show()=0;
    virtual ~Clothe(){}
};
class NikeClothe:public Clothe{
public:
    void show(){
        std::cout<<"nike clothe"<<std::endl;
    }
};
class Shoes{
public:
    virtual void show()=0;
    virtual ~Shoes(){}
};
class NiKeShoes:public Shoes{
public:
    void show(){
        std::cout<<"nike shoes"<<std::endl;
    }
};

class Factory{
public:
    virtual Shoes *CreateShoes()=0;
    virtual Clothe*CreateClothe()=0;
    virtual ~Factory(){}
};
class NiKeProducer:public Factory{
public:
    Shoes *CreateShoes(){
        return new NiKeShoes();
    }
    Clothe *CreateClothe(){
        return new NikeClothe();
    }
};
int main(){
    Factory *niKeProducer=new NiKeProducer();
    Shoes *nikeShoes=niKeProducer->CreateShoes();
    Clothe *nikeClothe=niKeProducer->CreateClothe();
    nikeShoes->show();
    nikeClothe->show();
    delete nikeClothe;
    delete nikeShoes;
    delete niKeProducer;
}
