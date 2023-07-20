#include<iostream>
#include<string>
using namespace std;
//不同的原料 每个原料都是一个类
class Douch{
public:
    Douch(){};
    ~Douch(){};
};
class Sauce{
public:
    Sauce(){};
    ~Sauce(){};
};
class Cheese{
public:
    Cheese(){};
    ~Cheese(){};
};
class Veggies
{
public:
    Veggies(){};
    ~Veggies(){};
};
class Pepproni
{
public:
    Pepproni(){};
    ~Pepproni(){};
};
class Clams
{
public:
    Clams(){};
    ~Clams(){};
};
//各种原料的集中工厂
class PizzaIngredientFactory
{
public:
    PizzaIngredientFactory();
    ~PizzaIngredientFactory();
    //生产原料
    Douch* createDough(){std::cout<<"Dough"<<std::endl;return new Douch();}
    Sauce* createSauce(){std::cout<<"Sauce"<<std::endl;return new Sauce();}
    Cheese* createCheese(){std::cout<<"Cheese"<<std::endl;return new Cheese();};
    Veggies* createVeggies(){std::cout<<"Veese"<<std::endl;return new Veggies();};
    Pepproni* createPepproni(){std::cout<<"Pepproni"<<std::endl;return new Pepproni();};
    Clams*   createClams(){std::cout<<"Clams"<<std::endl;return new Clams();};
};
PizzaIngredientFactory::PizzaIngredientFactory(){};
PizzaIngredientFactory::~PizzaIngredientFactory(){};
//所有不同原料合成一个披萨，
class Pizza
{
public:
    Pizza();
    virtual ~Pizza();
    string m_name;
    Douch* m_douch;
    Sauce* m_sauce;
    Veggies* m_veggies;
    Cheese* m_cheese;
    Pepproni* m_pepproni;
    Clams* m_clam;
    virtual void prepare();
    void bake(){std::cout<<"Baked"<<std::endl;}
    void cut(){std::cout<<"Cut"<<std::endl;}
    void box(){std::cout<<"Box"<<std::endl;}
public:
    void setName(string name){m_name=name;}
    string getName(){return m_name;}
};
Pizza::Pizza(){}
Pizza::~Pizza(){}
void Pizza::prepare(){}
//各地可以根据自己的需求从工厂中选择自己的专属配置原料
class ChessPizza:public Pizza
{
private:
    PizzaIngredientFactory* m_ingredientFactory;//原料工厂，
public:
    ChessPizza(PizzaIngredientFactory* ingredientFactory){m_ingredientFactory=std::move(ingredientFactory);}
    void prepare()
    {
        std::cout<<"Prepearing"<<getName()<<std::endl;
        m_douch = m_ingredientFactory->createDough();//createDough 返回这个区域所使用的酱料
        m_sauce = m_ingredientFactory->createSauce();
        m_veggies = m_ingredientFactory->createVeggies();
        m_cheese = m_ingredientFactory->createCheese();
    }
};
//还可以有多个类，来表示地区自己的
//一个加盟店所应有的基本的属性，不同地区的店在具体实现
class PizzaStore
{
public:
    PizzaStore();
    ~PizzaStore();
    virtual Pizza* orderPizza(string item);
};
Pizza* PizzaStore::orderPizza(string item){
return nullptr;
}
PizzaStore::PizzaStore(){}
PizzaStore::~PizzaStore(){}
//加盟店 需要他们使用了正确的披萨，也需要他们能和本地的原料的工厂搭上线
class NYPizzaStore :public PizzaStore
{
public:

    Pizza* create(string item)
    {
        Pizza *pizza=nullptr;
        //  纽约店会用到纽约披萨原料工厂，有该原料工厂负责生产所有纽约风味披萨所需的原料
        PizzaIngredientFactory *pizzaIngredientFactory=new PizzaIngredientFactory();
        // 披萨风味
        if(item=="chess")
        {
            //把工厂传递给每一个披萨，以便披萨能从工厂中取得原料
            pizza=new ChessPizza(pizzaIngredientFactory);   //选择原料工厂，接着在pizzastore中实例化，然后将他传递每个披萨的构造器
            pizza->setName("New York style cheese pizza");
            pizza->prepare();//工厂将被要求准备原料 
            return pizza;
        }
        else//以下风味待补充
        {
            return nullptr;
        }
    }
    Pizza* orderPizza(string item)
    {
        Pizza *pizza=create("chess");//创建pizza
        return pizza;
    }


};

int main()
{
    PizzaStore *nypizzaStore=new NYPizzaStore();//现在有了一个披萨店
    Pizza *pizza = nypizzaStore->orderPizza("chess");  //开始接受订单，

    return 0;
}