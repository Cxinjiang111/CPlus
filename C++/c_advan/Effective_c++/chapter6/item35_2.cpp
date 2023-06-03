/*藉由trl::function完成Strategy模式
一旦习惯了templates以及它们对隐式接口（见条款4l)的使用， 
基于函数指针的做法看起来便过分苛刻而死板了。 为什么要求 
“健康指数之计算“ 必须是个函数， 而不能是某种 “像函数的东西” 
（例如函数对象）呢？如果一定得是函数， 为 什么不能够是个 
成员函数？为什么一定得返回int而不是任何可被转换为int的类型呢？
如果我们不再使用函数指针 （如前例的healthFunc)， 而是改用一 
个类型为 trl::function的对象， 这些约束就全都挥发不见了。 就像条款54 所说，这样的
对象可持有（保存）任何可调用物(callable entity, 也就是函数指针、 函数对象、
或成员函数指针）， 只要其签名式兼容千需求端。以下将刚才的设计改为使用七rl::function:
函数指针出场
*/
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
//同一任务类型之不同实体可以有不同的健康计算函数，
class EvilBadGuy:public GameCharacter{
public:
    explicit EvilBadGuy(HealthCalcFunc hcf=defaultHealthCalc):GameCharacter(hcf){}
};
int loseHealthQuickly(const GameCharacter&)
{
}
int loseHealthSlowy(const GameCharacter&)
{
}
class EvilGoodGuy:public GameCharacter{
public:
    explicit EvilGoodGuy(HealthCalcFunc hcf=defaultHealthCalc):GameCharacter(hcf){}
};

int main()
{
    EvilBadGuy beg1(loseHealthQuickly);
    EvilBadGuy beg2(loseHealthSlowy);

    return 0;
}