#include<functional>
using namespace std;
class GameCharacter;
int defaultHealthCalc(const GameCharacter&);//外部函数 但是带基类
class GameCharacter{
public:
    typedef std::function<int(const GameCharacter&)>HealthCalcFunc;//函数指针
    explicit GameCharacter(HealthCalcFunc hcf=defaultHealthCalc):healthFunc(hcf)//构造函数
    {}
    int healthValue()const{
        return healthFunc(*this);
    }
private:
    HealthCalcFunc healthFunc;//提供指向函数的函数指针
};
short calcHealth(const GameCharacter);
struct HealthCalcuator{
    int operator()(const GameCharacter&)const{}
};
class EvilBadGuy:public  GameCharacter{
};
class EyeCandyCharacter:public  GameCharacter{
};
EvilBadGuy ebg1(calcHealth)//方法1，使用某个函数计算健康指数
{

}
EyeCandyCharacter ecc1(HealthCalcuator());//方法2，使用函数对象计算健康指数
GameLevel currentLevel;
//·                                    成员函数
EvilBadGuy beg2(std::bind(&GameLevel::health,currentLevel,_1));//方法3，使用成员函数计算健康指数




 
