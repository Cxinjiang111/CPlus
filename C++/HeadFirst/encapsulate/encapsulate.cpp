#include<iostream>
using namespace std;
#define FIRST 0

/*
class Coffee
{
public:
    void  prepareRecipe()
    {
        boilWater();
        brewCoffeeGrinds(); ///
        pourInCup();
        addSugarAndMilk(); /// pour
    }
    void boilWater()
    {
        std::cout <<" boilWater "<< std::endl;
    }
    void brewCoffeeGrinds()
    {
        std::cout<<"brewCoffeeGrinds "<< std::endl;
    }
    void pourInCup()
    {
        std::cout<<" pourInCup "<< std::endl;
    }
    void  addSugarAndMilk()
    {
        std::cout<<" addSugarAndMilk "<< std::endl;
    }
};
class Tea
{
public:
    void  prepareRecipe()//抽象化
    {
        boilWater();
        steepTeaBag(); ///
        pourInCup();
        addLemon(); /// pour
    }
    void boilWater()
    {
        std::cout <<" boilWater "<< std::endl;
    }
    void steepTeaBag()
    {
        std::cout<<"brewTeaGrinds "<< std::endl;
    }
    void pourInCup()
    {
        std::cout<<" pourInCup "<< std::endl;
    }
    void  addLemon()
    {
        std::cout<<" addSugarAndMilk "<< std::endl;
    }
};*/
class CaffeineBeverage
{
private:

public:
    CaffeineBeverage();
    ~CaffeineBeverage();
    void  prepareRecipe()
    {
        brew();
        addCondiments();
        boilWater();
        pourInCup();
    }
    virtual void brew();
    virtual void addCondiments();
    void boilWater(){std::cout<<"boilWater "<< std::endl;};
    void pourInCup(){std::cout<<"pourInCup "<<std::endl;};
};
CaffeineBeverage::CaffeineBeverage(){}
CaffeineBeverage::~CaffeineBeverage(){}
 void CaffeineBeverage::brew(){}
 void CaffeineBeverage::addCondiments(){}
class Tea:public CaffeineBeverage
{
public:

    void brew(){std::cout<<"Tea brew "<< std::endl;};
    void addCondiments(){std::cout<<"Tea addCondiments"<< std::endl;}
};

class Coffee:public CaffeineBeverage
{
public:
    void brew(){std::cout<<"Coffee brew "<< std::endl;};
    void addCondiments(){std::cout<<"Coffee addCondiments"<< std::endl;}
};
int main()
{
    Tea *ptea=new Tea();
    Coffee *pcoffee=new Coffee();
    ptea->prepareRecipe();
    pcoffee->prepareRecipe();
    return 0;
}




