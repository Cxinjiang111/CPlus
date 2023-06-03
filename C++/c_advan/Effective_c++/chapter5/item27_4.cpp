/*
种做法可让你通过base class接口处理”所有可能之各种Window派生类 “ ,
那就是在base class内提供virtual函数做你想对各个Window派生类做的事。
举个例子，虽然只有SpecialWindows可以闪烁，但或许将闪烁函数声明千base class内并 
提供一份 “什么也没做＂ 的缺省实现码是有意义的：

*/
#include<memory>
#include<vector>
class Window{
public:
    virtual void blink(){}
};
class SpecialWindow:public Window{
public:
    virtual void blink(){};
};
typedef std::vector<std::shared_ptr<Window>> VPW;
int main()
{
    VPW winptrs;
    for(VPW::iterator iter=winptrs.begin();iter!=winptrs.end();++iter)
    {
            (*iter)->blink();
    }
}