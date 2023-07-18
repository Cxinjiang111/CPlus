#include<iostream>
#include<string>
using namespace std;
//基类提供的披萨本身的特性
// //低层组件
class Pizza
{
public:
    Pizza(){}
    ~Pizza(){}
    virtual void prepare();
    virtual void bake();
    virtual void cut();
    virtual void box();
};
void Pizza::prepare(){}
void Pizza::bake(){}
void Pizza::cut(){}
void Pizza::box(){}
//基类提供经营加盟店的所应该的流程
// //高层组件 PizzaStore 依赖Pizza
class PizzaStore //
{
public:
    PizzaStore();
    ~PizzaStore();
    virtual Pizza* createPizza(string item);
    //提供披萨的流程
    virtual Pizza *orderPizza(string type);
};
Pizza* PizzaStore::orderPizza(string type)
{
    Pizza *pizza;
    pizza = createPizza(type);
    pizza->prepare();
    pizza->bake();
    pizza->box();
    pizza->cut();
    return pizza;
}
Pizza* PizzaStore::createPizza(string item){}
PizzaStore::PizzaStore(){}
PizzaStore::~PizzaStore(){}
//----------------------
// class NYStyleCheesePizza:public Pizza
// {
//     void prepare()
//     {
//         std::cout<<"NYStylecheesePizza"<<std::endl;
//     }
//     void bake()
//     {
//         std::cout<<"NYStylecheesePizza"<<std::endl;
//     }
//     void cut()
//     {
//         std::cout<<"NYStylecheesePizza"<<std::endl;
//     }
//     void box()
//     {
//         std::cout<<"NYStylecheesePizza"<<std::endl;
//     }
// };
// class NYStyleVeggiePizza:public Pizza
// {
//     void prepare()
//     {
//         std::cout<<"NYStyleVeggiePizza"<<std::endl;
//     }
//     void bake()
//     {
//         std::cout<<"NYStyleVeggiePizza"<<std::endl;      
//     }
//     void cut()
//     {
//         std::cout<<"NYStyleVeggiePizza"<<std::endl;
//     }
//     void box()
//     {
//         std::cout<<"NYStyleVeggiePizza"<<std::endl;
//     }    
// };
// class NYStylePepproniPizza:public Pizza
// {
//     void prepare()
//     {
//         std::cout<<"NYStylePepproniPizza"<<std::endl;
//     }
//     void bake()
//     {
//         std::cout<<"NYStylePepproniPizza"<<std::endl;
//     }
//     void cut()
//     {
//         std::cout<<"NYStylePepproniPizza"<<std::endl;
//     }
//     void box()
//     {
//         std::cout<<"NYStylePepproniPizza"<<std::endl;
//     }
// };
// //纽约
// class NYPizzaStore:public PizzaStore
// {
//     Pizza* createPizza(string item)
//     {
//         if(item=="cheese")
//         {
//             return new NYStyleCheesePizza();
//         }
//         else if(item=="VeggiePizza")
//         {
//             return new NYStyleVeggiePizza();
//         }
//         else if(item=="pepperoni")
//         {
//             return new NYStylePepproniPizza();
//         }
//         else
//         {
//             return nullptr;
//         }
//     }
// };

//加州地区类型的风味选择
class JIAStyleCheesePizza:public Pizza
{
    void prepare()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }
    void bake()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }
    void cut()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }
    void box()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }    
};
class JIAStyleClamPizza:public Pizza
{
    void prepare()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }
    void bake()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl; 
    }
    void cut()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }
    void box()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }    
};
class JIAStyleVeggiePizza:public Pizza
{
    void prepare()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }
    void bake()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }
    void cut()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }
    void box()
    {
        std::cout<<"JIAStyleCheesePizza"<<std::endl;
    }     
};
//所在加州内部地区想各自选择的风味
class JIAPizzaStore:public PizzaStore
{
public:
    JIAPizzaStore();
    ~JIAPizzaStore();
    Pizza* createPizza(string item)override;
private:
    Pizza *m_pizza;
};
Pizza*JIAPizzaStore::createPizza(string item)
{
    if(item=="CheesePizza")
    {
        return new JIAStyleCheesePizza();
    }
    else if(item=="VeggiePizza")
    {
        return new JIAStyleVeggiePizza();
    }
    else if(item=="ClamPizza")
    {
        return new JIAStyleClamPizza();
    }
    else
    {
        return nullptr;
    }
}
JIAPizzaStore::JIAPizzaStore(){}
JIAPizzaStore::~JIAPizzaStore(){}
int main()
{
    PizzaStore *pjiastore=new JIAPizzaStore();
    string s("CheesePizza");
    Pizza* pizaa=pjiastore->orderPizza(s);
    return 0;
}