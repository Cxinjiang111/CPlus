/*
然而假设Widget和WidgetImpl都是class template而非classes，
也许我们可以试试将WidgetImpl内的数据类型加以参数化
template<typename T>
class WidgetImpl{};
template<typename T>
class Widget{};
*/
#include<vector>
#include<iostream>
namespace std{
class WidgetImpl{ //作为一种存放数据的指针
public:
    
private:
    int a,b,c;//可能许多数据
    std::vector<double> v;//意味复制时间很长
};
class Widget{
public:
    void swap(Widget&other){
        using std::swap;
        std::swap(pImpl,other.pImpl);
    }

private:
    WidgetImpl *pImpl;
};
//特化版本
template<>
void swap<Widget>(Widget &a,Widget&b){
    a.swap(b);
}
//error 看起来像实现模板类当成模板特化使用
// template<typename T>
// void swap<Widget<T> >(Widget<T>&a,Widget<T>&b)
// {
//     a.swap(b);
// }

//当你打算偏特化一个function template时，做法就是简单的为他添加一个重载版本
    // template<typename T>
    // void swap(Widget<T>&a,Widget<T>&b){
    // a.swap(b);
    // }


}

namespace WidgetStuff{
    template<typename T>
    void swap(Widget<T>&a,Widget<T>&b)
    {
        a.swap(b);
    }
}