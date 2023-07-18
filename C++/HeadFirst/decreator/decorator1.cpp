#include<iostream>
#include<string>
using namespace std;
class Beverage{
public:
    Beverage(){};
    ~Beverage(){};
    string description="Unknown Beverage";
    virtual string getDescription()
    {
        return description;
    }
    virtual double cost(){};
};
//调料代码
class CondimentDecorator: public Beverage{
public:
    string getDescription(){};
};
class Espresso: public Beverage{
public:
    Espresso(){
        description="Espresso";
    }
    ~Espresso(){}
    double cost(){
        return 1.99;//水 任意饮料都需要的
    }
};
class Espresso1: public Beverage{
public:
    Espresso1(){
        description="Espresso";
    }
    ~Espresso1(){}
    double cost(){
        return 3;
    }
};

class CondimentDecorator1: public Beverage{
public:
    string getDescription(){};
};

//样式代码
class Mocha :public CondimentDecorator{
public:
    Mocha(Beverage beverage)
    {
        this->m_beverage=beverage;
    }
    string getDescription()
    {
        return m_beverage.getDescription()+"Mocha";
    }
    double cost()
    {
        return 2.0+m_beverage.cost();
    }
private:
    Beverage m_beverage;
};
class coffe :public CondimentDecorator{
public:
    coffe(Beverage beverage)
    {
        this->m_beverage=beverage;
    }
    string getDescription()
    {
        return m_beverage.getDescription()+"Mocha";
    }
    double cost()
    {
        return 3.0+m_beverage.cost();
    }
private:
    Beverage m_beverage;
};
int main()
{
    Beverage *pspresso=new Espresso();//
    Beverage *pspresso1= new Espresso();
    // std::cout<<pspresso->getDescription()<<std::endl;
    // std::cout<<pspresso->cost()<<std::endl;
    //这个就是Mocha+coffe组成
    pspresso= new Mocha(*pspresso);
    pspresso= new coffe(*pspresso);
    // std::cout<<pspresso->getDescription()<<std::endl;
    // std::cout<<pspresso->cost()<<std::endl;
    //这个咖啡是由调料1+调料2
    pspresso =new coffe(*pspresso);
    pspresso= new coffe(*pspresso1);
    std::cout<<pspresso->getDescription()<<std::endl;
    std::cout<<pspresso->cost()<<std::endl;
    // //这个咖啡是由coffe+调料2
    pspresso =new Mocha(*pspresso);
    pspresso= new coffe(*pspresso1);
    ///两种区域给分开，然后任意组合 
    return 0;
}