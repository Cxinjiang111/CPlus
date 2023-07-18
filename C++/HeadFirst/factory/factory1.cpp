#include<iostream>
#include<string>
using namespace std;
//并不算真正的工厂类，但有点像批量生产的过程
class Pizza
{
public:
    virtual void prepare();
    virtual void bake();
    virtual void cut();
    virtual void box();
};
class CheesePizza:public Pizza
{
};
class ClamPizza:public Pizza
{
};
class VeggiePizza:public Pizza
{
};
class SimplePizzaFactory
{
public:
    //创建各种对象，
    Pizza* createPizza(string type)
    {
        Pizza *pizza=nullptr;
        if(type=="chess")
        {
            pizza= new CheesePizza();
        }
        else if(type=="pepperoni")
        {
            pizza= new ClamPizza();
        }
        else if(type=="Veggie")
        {
            pizza= new VeggiePizza();
        }
        return pizza;
    }
};
class PizzaStore
{
private:
    SimplePizzaFactory m_factory;
    PizzaStore(SimplePizzaFactory factory)
    {
        m_factory=std::move(factory);
    }
    Pizza *orderPizza(string type)
    {
        Pizza *pizza=m_factory.createPizza("chess");
        pizza->prepare();
        pizza->bake();
        pizza->box();
        pizza->cut();
        return pizza;
    }
};
