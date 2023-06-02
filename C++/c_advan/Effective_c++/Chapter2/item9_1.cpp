#include<string>
/*
但是侦测 “ 构造函数或析构函数运行期间是否调用virtual函数 ” 并不总是这般轻松。 如果Transac豆on有多个构造函数， 每个都需执行某些相同工作， 那么避免 代码重复的一个优秀做法是把共同的初始化代码（其中包括对logTransaction的调 用）放进 一个初始化函数如init内：

*/
class Transaction{
public:
    Transaction()//这里调用non-virtual
    {
        init();
    }
    //做一份因类型不同而不同的日志记录
    virtual void  logTransaction()const=0;
private:
    void init(){
        logTransaction();//这里调用virtual
    }
};

/*
这段代码概念上和稍早版本相同， 但它比较潜藏并且暗中为害， 因为它通常不会引发任何编译器和连接器的抱怨。 此时由千logTransaction是Transaction内
的一个pure virtual函数， 当pure virtual函数被调用， 大多执行系统会中止程序（通常会对此结果发出一个信息），
 然而如果logTransaction是个正常的（也就是impure) virtual函数并在Transaction内带有一份实现代码， 该版本就会被调用，
 而程序也就会兴高采烈地继续向前行，留下你百思不解为什么建立一个derivedclass对象时会调用错误版本的logTransaction。唯一
 能够避免此问题的做法就是：确定你的构造函数和析构函数都没有（在对象被创建和被销毁期间）调用virtual函数，而它们调用的所有函数也都服从同一约束
*/




/*
其他方案可以解决这个问题。一种做法是在classTransaction内将 logTransaction函数改为non-virtual,
然后要求derivedclass构造函数传递必要信息给Transaction构造函数，
*/

class Transaction{
public:
    explicit Transaction(const std::string&logInfo);
    void logTransaction(const std::string&logInfo);

};

Transaction:: Transaction(const std::string&logInfo)
{
    logTransaction(logInfo);
}
class BuyTransaciton:public Transaction{
public:
    //将log信息传给base class构造函数
    BuyTransaciton(std::string param):Transaction(createLogString(param))
    {

    }
private:
    static std::string createLogString(std::string& param);

};
/*
换句话说由千你无法使用virtual函数从base classes向下调用， 在构造期间， 你可以藉由 “ 令derived classes将必要的构造信息向上传递至base class构造函数” 替换之而加以弥补。

请注意本例之BuyTransaction内的private static函数crea七eLogString的运 用。是的，比起在 成员初值列(m ember initialization list )内给予base class所需数据，利用辅助函数创建一个值传给base class构造函数往往比较方便（也比较可读）。令此函数为static,也就不可能意外指向 “初期未成熟之BuyTransaction对象内尚未 初始化的成员变量 ” 。这很重要， 正是因为“那些成员变植处千未定义状态” ，所 以 “ 在base class构造和析构期间调用的virtual函数个可下降允derived classes"。
*/