/*
但即使如此，upperLeft和lowerRight还是返回了“代表对象内部 ”的handles,
有可能在其他场合带来问题。 更明确地说，它可能导致danglinghandles（空悬的号
码牌）：这种handles所指东西（的所属对象）不复存在。这种“不复存在的对象”
最常见的来源就是函数返回值。例如某个函数返回GUI对象的外框(boundingbox), 这个外框采用矩形形式：
*/
class GUIOBject{

};
#include<memory>
class Point{
public:
    Point(int x_,int y_);
    void setX(int newval);
    void setY(int newval);
private:
    int x,y;
};
struct RectData{
    Point ulhc;
    Point lrhc;
};
class Rectangle{
    const Point&upperLeft()const {return pData->lrhc;}//调用者能够使用被返回的reference来更改成员,但rec其实应该时不可变的
    const Point&lowerRight()const {return pData->ulhc;}  
    //Rectangle(Point&  p1,Point &p2):pData.ulhc(p1){}; ??error
private:
    std::shared_ptr<RectData> pData;//4字节指针，降低了Rectangle结构体大小
};
const Rectangle  boundingBox(const GUIOBject&obj);
GUIOBject *pgo;
//取得一个指针指向外框左上点
const Point *pUpperLeft=&(boundingBox(*pgo).upperLeft());
/*
对boundingBox的调用获得 个新的、暂时的Rectangle对象。这个对象没有名称，
所以我们权且称它为temp。 随后 upperLeft作用于temp身上，返回一个 reference 指向 temp的
 一个内部成分， 更具体地说是 指向一个用以标示temp的 Points。 于是 pUpperLeft指向那个Point对象。
目前为止 一切还好， 但故事尚未结束，因为在那个语旬结束之后，boundingBox的返回值，
也就是我们所说的temp,将被销毁， 而那间接导致temp内的Points析构。最终导致pUpperLeft指向一个不再存在的对象；
也就是说 一旦产出pUpperLeft的那个语句结束，pUpperLeft也 就变成空悬、 虚吊(dangling) ! 

这就是为什么函数如果”返回 个handle代表对象内部成分 “总是危险的原因 。
不论这所谓的 handle是个指针或迭代器或reference,也不论这个 handle是否为 const, 
也不论那个返回handle 的成员函数是否为const。这里的唯一关键是， 有 
个handle被传出去 f，一旦如此你就是暴露在 “handle比其所指对象更长寿” 的风险下。
这并不意味你绝对不可以让成员函数返回handle。 有时候你必须那么做。 例如 operator[］
就允许你 “ 摘采"strings和vectors的个别元素，曲这些operator[]s 就是返回references指向 
“ 容器内的数据 “ （见条款3)， 那些数据会随着容器被 销毁而销毁。 尽管如此，这样的函数毕竟是例外，不是常态
*/