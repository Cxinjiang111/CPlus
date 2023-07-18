#include<iostream>
#include<string>
using namespace std;
//不同的原料
class Douch{

};
class Sauce{
    
};
class Cheese{
    
};
class Veggies
{

};
class Pepproni
{

};
class Clams
{

};
class PizzaIngredientFactory
{
public:
    //生产原料
    Douch createDough();
    Sauce createSauce();
    Cheese createCheese();
    Veggies createVeggies();
    Pepproni createPepproni();
    Clams   createClams();
};

