#include<vector>
#include<algorithm>
using namespace std;
class Widget{};
//写法 1
vector<Widget> vw;
Widget bestWidget;
//寻找与bestWidget相等的项
vector<Widget>::iterator it=std::find(vw.begin(),vw.end(),bestWidget);
//上述写法不好
//这时改变 容器类型变得容易的多
//写法 2
typedef vector<Widget> WidgetContainer;//定义容器，进行了以此小的封装
typedef WidgetContainer::iterator WContainer;//取新定义容器下的迭代器名称
WidgetContainer cw;
Widget bestWidget;

WContainer i=find(cw.begin(),cw.end(),bestWidget);
//写法 3
template<typename T>
class SpecialAllocator{

};
typedef vector<Widget,SpecialAllocator<Widget>> WidgetContainer;//自己附带一个分配器
typedef WidgetContainer::iterator WCIterator;

WidgetContainer cw;//在写法23的情况下均可使用，体现了一定的泛化能力
Widget bestWidget;

WCIterator i=find(cw.begin(),cw.end(),bestWidget);//在写法23的情况下均可使用，体现了一定的泛化能力


