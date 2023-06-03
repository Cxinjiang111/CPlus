/*条款40：使仿函数类可适配*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<list>
#include<set>
#include<deque>
#include<string>
#include<iterator>
#include<functional>
using namespace std;
class Widget{

};
bool isInteresting(const Widget*pw);
void t1()
{
    list<Widget*>widgetPtrs;
    // list<Widget*>::iterator i=find_if(widgetPtrs.begin(),widgetPtrs.end(),isInteresting);
    // if(i!=widgetPtrs.end())//找到了
    // {

    // }
    //但如果我想要找第一个指向不有趣的Widget的指针，显而易见的方法却编译失败：
    list<Widget*>::iterator i =find_if(widgetPtrs.begin(), widgetPtrs.end(),not1(isInteresting)); // 错误！不能编译
}
void t1()
{
    list<Widget*>widgetPtrs;
    list<Widget*>::iterator i =find_if(widgetPtrs.begin(), widgetPtrs.end(),not1(ptr_func(isInteresting))); // 错误！不能编译

}
/*
答案多少有些令人惊讶。ptr_fun做的唯一的事是使一些typedef有效。就是这样。not1需要这些typedef，这就
是为什么可以把not1应用于ptr_fun，但不能直接对isInteresting应用not1。因为是低级的函数指针，isInteresting
缺乏not1需要的typedef。
not1不是STL中唯一有那些要求的组件。四个标准函数适配器（not1、not2、bind1st和bind2nd）都需要存在某
些typedef，一些其他人写的非标准STL兼容的适配器（比如来自SGI和Boost的——参见条款50）也需要。提供
这些必要的typedef的函数对象称为可适配的，而缺乏那些typedef的函数对象不可适配。可适配的比不可适配
的函数对象可以用于更多的场景，所以只要能做到你就应该使你的函数对象可适配。这
*/
int main()
{
    t1();


    return 0;
}













