/*考虑写出一个不抛异常的swap函数
*/
#include<vector>
namespace std{
    template<typename T>
    void swap(T&a,T&b)
    {
        T temp(a);
        a=b;
        b=temp;
    }
}
//以指针指向一个对象，内含真正数据的那种类型，
class WidgetImpl{ //作为一种存放数据的指针
public:
    
private:
    int a,b,c;//可能许多数据
    std::vector<double> v;//意味复制时间很长
};
class Widget{
public:
    Widget(const Widget&rhs);
    Widget&operator=(const Widget&rhs)
    {
        *pImpl=*(rhs.pImpl);
    }
private:
    WidgetImpl *pImpl;
};
//一旦要置换两个Widget对象值，我们唯一需要做的就是置换pImpl指针，6666
//这样就不需要构造那么多临时数据进行swap了
namespace std{
    template<> //这是个Widget的特化版本
    void swap<Widget>(Widget&a,Widget&b)
    {
        swap(a.pImpl,b.pImpl);
    }
}


