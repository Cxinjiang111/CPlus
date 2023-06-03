/*条款33：提防在指针的容器上使用类似remove的算法*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<string>
using namespace std;
class Widget{
public:
    bool isCertified()const;
};
void delAndNullifyUncertified(Widget*&pWidget)
{
    if(pWidget->isCertified())
    {
        delete pWidget;
        pWidget=nullptr;
    }
}
void  t1()
{
    vector<Widget*>v;//好危险 尽量不要把指针放到容器中，太危险了
    v.push_back(new Widget);
    //我决定删除,某些指针

   //v.erase(remove_if(v.begin(),v.end(),notl(mem_fun(&Widget::isCertified))),v.end());
    //突然你开始担心erase的调用，因为你朦胧的记起条款7关于摧毁容器中的一个指针也不会删除指针指向的东西
    //的讨论。这是个合理的担心，但在这里，太晚了。当调用erase时，极可能你已经泄漏了资源。担心erase，是
    //的，但首先，担心一下remove_if。

//把所有指向未通过检验Widget的指针删除并且设置为空
    for_each(v.begin(),v.end(),delAndNullifyUncertified);
    //把v中除去空指针
    v.erase(remove(v.begin(),v.end(),
    static_cast<Widget*>(0)), //0必须映射到一个空指针
    v.end());
    //让C++可以正确推出remove的第三个参数的类型

}
//总结不要用这玩意，用就用带引用计数的智能指针
















