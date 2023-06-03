/*考虑virtual函数以外的其他选择
*/
class GameCharacter{
public:
    //这里并没申明为pure virtual，暗示我们将会有个计算健康指数的缺省算法
    virtual int healthValue()const;//返回人物的健康质数
};
//藉由non-virtual interface手法实现template method模式
class GameCharacter{
public:
    int healthValue()const{ //在class定义式内呈现成员函数本体 
    //也就让他们全都暗自成了inline
    //....可做事前工作 设定函数之前适当的场景 比如保存现场
        int retVal=doHealthValue();
        //.....可做事后工作  清理现场
        return retVal;
    }
    //这种通过public non-virtual成员函数间接调用private virtual函数称为NVI手法

private:
    virtual int doHealthValue()const{

    }
};
/*
NVI手法的一个优点隐身在上述代码注释 “ 做一些事前工作” 和 “ 做一些事后 工作 ” 之中。 
那些注释用来告诉你当时的代码保证在 “ virtual函数进行真正工作之 前和之后” 被调用。 
这意味外覆器(wrapper)确保得以在一个virtual 函数被调用 之前设定好适当场景， 
并在调用结束之后清理场景。 “事前工作 “可以包括锁定互斥器(locking a mutex)、
 制造运转日志记录项(log entry)、 验证class约束条件、 验证函数先决条件等等。
 ”事后工作“可以包括互斥器解除锁定(unlocking a mutex)、 验证函数的事后条件、
 再次验证class约束条件等等。如果你让客户直接调用virtual函数， 就没有任何好办法可以做这些事。

有件事实或许会妨碍你跃跃欲试的心： NVI手法涉及在 derived classes内重新
定义private virtual函数。啊， 重新定义若干个derived classes并不调用的函数！这
里并不存在矛盾。 重新定义 virtual函数 表示某些事 如何 被完成， 调用
virtual 函数” 则表示它 “何时” 被完成。 这些事情都是各自独立互不相干的。 NVI
手法允许derived classes重新定义virtual函数， 从而赋予它们 “如何实现机能” 的
控制能力， 但base class保留诉说 “函数何时被调用” 的权利。 一开始这些听起来
似乎诡异，但C+＋的这种 “ derived classes可重新定义继承而来的private virtual函
”数 的规则完全合情合理。

在NVI手法下其实没有必要让virtual函数一定得是private。 某些class继承体系要求derived 
class在virtual函数的实现内必须调用其base class 的对应兄弟（例如p.120的程序）， 
而为了让这样的调用合法， virtual 函数必须是protected, 不能是 private。 
有时候virtual函数甚至一定得是public（例如具备多态性质的base classes的析构函数—见条款7)， 
这么一来就不能实施NVI手法了。

*/