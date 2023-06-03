/*
在探究dynamic_cast设计意涵之前，值得注意的是，dynamic_cast的许多实 
现版本执行速度相当慢。例如至少有一个很普遍的实现版本基于 “class名称之字符串比较” ，
如果你在四层深的单继承体系内的某个对象身上执行dynamic_cast, 刚才说的那个实现版本所提供的
每一次dynamic_cast可能会耗用多达四次的 strcmp调用，用以比较class名称。 
深度继承或多重继承的成本更高！某些实现版 本这样做有其原因（它们必须支持动态连接）。
然而我还是要强调，除了对一般转型保持机敏与猜疑，更应该在注重效率的代码中对dynamic_casts保待机敏与猜疑。

之所以需要dynamic_cast,通常是因为你想在一个你认定为derivedclass对象
身上执行derived class操作函数，但你的手上却只有一个 ” 指向base"的pointer或 reference, 
你只能靠它们来处理对象。有两个一般性做法可以避免这个问题。

第一，使用容器并在其中存储直接指向derived class对象的指针（通常是智能指针， 见条款13)，
 如此便消除了 “通过base class接口处理对象” 的需要。 假设先前的Window/SpecialWindow继承体系
 中只有SpecialWindows才支持闪烁效果， 试着不要这样做：
*/
#include<memory>
#include<vector>
class Window{
public:
    virtual void  f();
    Window();
};
class SpecialWindow:public Window{
public:
    void blink();
};
typedef std::vector<std::shared_ptr<Window>> VPW;
int main()
{
    VPW winptrs;
    for(VPW::iterator iter=winptrs.begin();iter!=winptrs.end();++iter)
    {
        if(SpecialWindow*psw=dynamic_cast<SpecialWindow*>(iter->get()))
                psw->blink();        //不应该这么做
               // (*iter)->blink(); //应该这么做
    }
}
/*
当然啦， 这种做法使你无法在同一个容器内存储指针 ” 指向所有可能之各种 阻ndow派生类” 。
如果真要处理多种窗口类型，你可能需要多个容器，它们都必须具备类型安全性(type-safe)。
*/

