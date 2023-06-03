/*藉由 Function Pointers 实现 Strategy 模式

NVI手法对public virtual函数而言是一个有趣的替代方案，
但从某种设计角度观之，它只比窗饰花样更强一些而已。
毕竟我们还是使用virtual函数来计算每个人物的健康指数。 
另一个更戏剧性的设计主张 “ 人物健康指数的计算与人物类型无关，
这样的计算完全不需要 “ 人物” 这个成分。 
例如我们可能会要求每个人物的构造函数接受一个指针，
指向一个健康计算函数， 而我们可以调用该函数进行实际 计算：

*/
class GameCharacter;
int defaultHealthCalc(const GameCharacter&gc);//外部函数 但是带基类
class GameCharacter{
public:
    typedef int (*HealthCalcFunc)(const GameCharacter&);//函数指针
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
/*
某已知人物之健康指数计算函数可在运行期变更。例如GameCharacter可提供 
一个成员函数setHeal七hCalculator,用来替换当前的健康指数计算函数。

换句话说，“健康指数计算函数不再是GameCharacter继承体系内的成员函数”这一
事实意味，这些计算函数并未特别访问 ” 即将被计算健康指数 ” 的那个对象的
内部成分。 例如defaultHealthCalc并未访问EvilBadGuy的non-public成分。

如果人物的健康可纯粹根据该人物public接口得来的信息加以计算 ，这就没有
问题， 但如果需要non-public 信息进行精确计算， 就有问题了。 实际上任何时候当
你将class内的某个机能 （也许取道自某个成员函数）替换为class外部的某个等价
 机能（也许取道自某个non-member non-frie nd函数或另 一 个class的non-friend 
 成员函数），这都是潜在争议点。这个争议将持续至本条款其余篇幅， 因为我们即将考 
 虑的所有替代设计也都涉及使川GameCharacter继承体系外的函数。

一般而言， 唯一能够解决 “ 面要以non-mem ber函数访问 class的non-public成分
 的办法就是： 弱化class 的封装。例如class 可声明那个 non-member 函数为
friends， 或是为 其实现的某一部分提供public 访问函数（其他部分则宁可隐藏起来）。 
运用函数指针 替换virtual函数， 其优点（像是“每个对象可各自拥有自己的健康计算函数” 
和 “ 可在运行期改变计算函数” )是否足以弥补缺点（例如可能必须降低GameCharacter封装件），
 是你必须根据每个设计情况的不同而抉择的。
*/





