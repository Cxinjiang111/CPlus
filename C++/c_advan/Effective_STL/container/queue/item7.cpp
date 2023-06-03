/*儅使用new的指針容器時，記得在銷毀容器前delete那些指針
*/
//儅容器容納的是通過new分配的對象的指針時，就STL容器不能實現自己清理工作了
/*
当一个指针的容器被销毁时，会销毁它（那个容器）包含的每个元素，但指针的“析构函数”是
无操作！它肯定不会调用delete。

*/
#include<vector>
#include<memory>
#include<algorithm>
using namespace std;
#define SOME_MAGIC_NUMBER 20
class Widget{};
void doSomething()
{
    vector<Widget*> vwp;
    for(int i=0;i<20;++i)
    {
        vwp.push_back(new Widget);
    }
}
//当vwp除了生存域后，vwp的每个元素都被销毁，但那并不改变从没有把delete作用于new得到的对象这个事
//实。那样的删除是你的职责，而不是vector的。这是一个特性。只有你知道一个指针是否应该被删除。
void do1()
{
    vector<Widget*>vwp;
    for(vector<Widget*>::iterator i=vwp.begin();i!=vwp.end();++i)
    {
        delete *i;
    }
}
//這裏存在的問題就是銷毀的過程中存在異常，那麽還是存在内存泄漏

template<typename T>
struct DeleteObject:public unary_function<const T*,void>
{
    void operator()(const T* ptr)const 
    {
        delete ptr;
    }
    
};
void do2()
{
    vector<Widget*>vwp;
    for_each(vwp.begin(),vwp.end(),DeleteObject<Widget>);
}
