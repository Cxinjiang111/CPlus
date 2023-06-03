/*
for_each和accumulate的不同主要在两个方面。首先，accumulate的名字表示它是一个产生区
间统计的算法，for_each听起来好像你只是要对区间的每个元素进行一些操作，而且，当然，那是那个算法
的主要应用。用for_each来统计一个区间是合法的，
*/
#include<numeric>
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<set>
#include<string>
#include<iterator>
using namespace std;
struct Point
{
    Point(double initX ,double initY):x(initX),y(initY){}
    double x,y;
};
class PointAverage:public unary_function<Point,void>{
public:
    PointAverage():xSum(0),ySum(0),numPoints(0){}
    void operator()(const Point&p)
    {
        ++numPoints;
        xSum+=p.x;
        ySum+=p.y;
    }
    Point result()const{
        return Point(xSum/numPoints,ySum/numPoints);
    }
private:
    size_t numPoints;
    double xSum;
    double ySum;
};
void t3()
{
    vector<Point> vp;
    for(int i=0;i<6;++i)
    {
        //Point()
        vp.push_back({1.0*i,2.0*i});
    }
    // template<typename _InputIterator, typename _Function>
    // _Function for_each(_InputIterator __first, _InputIterator __last, _Function __f)
    Point sum= for_each(vp.begin(),vp.end(),PointAverage()).result();
    //还是有点难以理解
    std::cout<<"x: "<<sum.x<< "  y:  "<<sum.y<<endl;

}
int main()
{
    t3();
    return 0;
}





