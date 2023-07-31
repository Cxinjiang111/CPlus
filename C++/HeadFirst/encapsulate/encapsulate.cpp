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
public:
    CaffeineBeverage();
    ~CaffeineBeverage();
    //这是个基类的模板方法，定义其流程。
    void  prepareRecipe()
    {
        //brew();
       // addCondiments();
       // boilWater();
       // pourInCup();
        if(customerWantsCondiments())
        {
            addCondiments();
        }
        //hook();
    }
    virtual void brew();
    virtual void addCondiments();//这个定义为虚函数目的是为了让继承类实现自己的功能
    void boilWater(){std::cout<<"boilWater "<< std::endl;};//这个不是虚函数，也就是所有继承类都必须遵循的操作
    void pourInCup(){std::cout<<"pourInCup "<<std::endl;};
    //可以理解，我们抽出所有共性的东西，不同的东西有具有基类的函数去实现

    void hook(){};//这是一个具体的方法，但它什么事情也不做。也可以有默认的实现，我们称之为hook 钩子函数，
    //子类可以视情况决定要不要覆盖他们。
    //钩子的存在，可以让子类有能力对算法的不同点进行挂载，要不要挂钩，由子类自行决定。

    //这就是个钩子函数，我们可以通过返回true 或者false来决定是否需要addCondiments()函数。
    //这个钩子函数有子类去实现，通过继承类可以改变原有的流程，已实现自己的功能。这里可以返回enum类型
    //开出很多不同的分支，然后流程函数可以使用switch case
    virtual bool customerWantsCondiments();
};
bool CaffeineBeverage::customerWantsCondiments(){return false;}
CaffeineBeverage::CaffeineBeverage(){}
CaffeineBeverage::~CaffeineBeverage(){}
 void CaffeineBeverage::brew(){}
 void CaffeineBeverage::addCondiments(){}
class Tea:public CaffeineBeverage
{
public:

    void brew(){std::cout<<"Tea brew "<< std::endl;};
    void addCondiments(){std::cout<<"Tea addCondiments"<< std::endl;}
    bool customerWantsCondiments(){return true;}
};

class Coffee:public CaffeineBeverage
{
public:
    void brew(){std::cout<<"Coffee brew "<< std::endl;};
    void addCondiments(){std::cout<<"Coffee addCondiments"<< std::endl;}
    bool customerWantsCondiments(){     
        return false;}
};
int main()
{
    Tea *ptea=new Tea();
    Coffee *pcoffee=new Coffee();
    ptea->prepareRecipe();
    pcoffee->prepareRecipe();
    return 0;
}




