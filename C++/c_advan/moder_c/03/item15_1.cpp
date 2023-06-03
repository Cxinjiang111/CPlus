#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
#include<algorithm>
#include<array>
using namespace std;
class Point{
    public:
        constexpr Point(double xVal=0,double yVal=0)noexcept:x(xVal),y(yVal){}
        constexpr double xValue()const noexcept{return x;}
        constexpr double yValue()const noexcept{return y;}
        void setX(double newX )noexcept{x=newX;}
        void setY(double newY )noexcept{y=newY;}
    private:
        double x,y;
};
constexpr  Point midpoint(const Point&p1,const Point&p2)noexcept{
    return {(p1.xValue()+p2.xValue())/2,(p1.yValue()+p2.yValue())/2};
}
void t1(){
    
    constexpr Point  p1(2.1,2.3);
    constexpr Point  p2(1.0,3.0);
    constexpr auto mid=midpoint(p1,p2);
    cout<<mid.xValue()<<mid.yValue()<<endl;
    /*
这太令⼈激动了。它意味着mid对象通过调⽤构造函数，getter和成员函数就能在只读内存中创建！它也
意味着你可以在模板或者需要枚举量的表达式⾥⾯使⽤像mid.xValue()*10的表达式！它也意味着以前
相对严格的某⼀⾏代码只能⽤于编译期，某⼀⾏代码只能⽤于运⾏时的界限变得模糊，⼀些运⾏时的普
通计算能并⼊编译时。越多这样的代码并⼊，你的程序就越快。（当然，编译会花费更⻓时间）
    
    */
}
int main(){
    t1();
    return 0;
}