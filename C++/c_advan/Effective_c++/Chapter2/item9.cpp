/*绝不在构造和析构过程中调用virtual函数
在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class
*/
class Transaction{
public:
    Transaction();
    //做一份因类型不同而不同的日志记录
    virtual void  logTransaction()const=0;
};
Transaction::Transaction() //base class构造函数之实现
{
    logTransaction();//最后动作时日志这笔交易
}
//继承类
class BuyTransaction:public Transaction{
public:
    virtual void logTransaction()const;
};
//继承类
class SellTransaction:public Transaction{
public:
    virtual void logTransaction()const;
};

/*
无疑地会有一个BuyTransaction构造函数被调用， 但首先Transaction构造 函数一定会更早被调用；是的，derivedclass对象内的bas e class成分会在derived class 
自身成分被构造之前先构造妥当。 Transac巨on构造函数的最后一行调用virtual函 数logTransaction, 这正是引发惊奇的起点。 这时候被调用的logTransaction是 Transaction内的版本，不是BuyTransaction内的版本一即使目前即将建立的对 象类型是BuyTransaction。 是的， base class构造期间virtual函数绝不会下降到derived classes阶层。取而代之的是， 对象的作为就像隶属base 类型一样。非正式的 说法或许比较传神：在base class构造期间， virtual函数不是virtual函数。

这一似乎反直觉的行为有个好理由。由于base class构造函数的执行更早于derioved class构造函数，
造函数，当base class构造函数执行时deriv ed class的成员变量尚如果此期间调用的virtual函数下降至derivedclasses阶层，要知道 的函数几乎必然取用local成员变量， 而那些成员变量尚未初始化。这将 不明确行为和彻夜调试大会串的直达车票。 “要求使用对象内部尚未初始化的成分
是危险的代名词，所以C++不会让你走这条路



对象的类型是base class而不是derived class。 不只virtual函数会被编译器解析至
(resolve to) base class, 若使用运行期类型信息(runtime type information, 例如 dynamic cast（见条款27)和typeid)， 也会把对象视为base class类型。 本例之
中， 当Transaction构造函数正执行起来打算初始化 “ BuyTransaction对象内的 base class成分” 时， 该对象的类型是Transac巨on。 那是每 一个C+＋次成分（见条 款1)的态度， 而这样的对待是合理的：这个对象内的 “ BuyTransaction专属成分” 尚未被初始化，所以面对它们，最安全的做法就是视它们不存在。对象在derived class 构造函数开始执行前不会成为一个derived class对象。
相同道理也适用千析构函数。 一旦derived class析构函数开始执行， 对象内的 derived class成员变量便呈现未定义值， 所以C廿视它们仿佛不再存在。 进入base class析构函数后对象就成为一个base class对象， 而C+＋的任何部分包括virtual函 数、dynamic_casts等等也就那么看待它。

在上述示例中， Transaction构造函数直接调用一个virtual函数， 这很明显而 且容易看出违反本条款。 由千它很容易被看出来， 某些编译器会为此发出一个警告 信息（某些则否， 见条款53对警告信息的讨论）。 即使没有这样的警告， 这个问题 在执行前也几乎肯定会变得显而易见， 因为logTransaction函数在Transaction 内是个pure virtual。 除非它被定义（不太有希望， 但是有可能， 见条款34)否则程序无法连接， 因为连接器找不到必要的Transaction: : logTransaction实现代码。


*/