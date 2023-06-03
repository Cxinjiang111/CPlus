//但pImpl是private 上面没法编译
#include<vector>
#include<iostream>
class WidgetImpl{ //作为一种存放数据的指针
public:
    
private:
    int a,b,c;//可能许多数据
    std::vector<double> v;//意味复制时间很长
};
class Widget{
public:
    void swap(Widget*other){
        using std::swap;
        std::swap(pImpl,other.pImpl);
    }
private:
    WidgetImpl *pImpl;
};
template<>
void swap<Widget>(Widget &a,Widget&b){
    a.swap(b);
}