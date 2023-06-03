/*条款37：用accumulate或for_each来统计区间*/
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
int multi(int init,int num)
{
    return init*num;
}
void t1()
{
    vector<int> vd;
    for(unsigned i=1;i<5;++i)
    {
        vd.push_back(i);
    }
    //   template<typename _InputIterator, typename _Tp>
    //   _Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init)
    //double sum=accumulate(vd.begin(),vd.end(),0.0);


    //  template<typename _InputIterator, typename _Tp, typename _BinaryOperation>
    // _Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init, _BinaryOperation __binary_op)
    int sum=accumulate(vd.begin(),vd.end(),1,multi);
    cout<<sum<<endl;
}
string::size_type stringLengthSum(string::size_type sumSoFar,const string&s)
{
    return sumSoFar+s.size();
}
void t2()
{
    set<string> s;
    s.insert("hello");
    s.insert("world");
    s.insert("my");
    s.insert("name");
    string::size_type lengthSum=accumulate(s.begin(),s.end(),0,stringLengthSum);
    cout<<lengthSum<<endl;
}
struct Point
{
    Point(double initX ,double initY):x(initX),y(initY){}
    double x,y;
};
Point avage(Point& initPoint,Point& curPoint)
{
    Point temp(initPoint.x+curPoint.x,initPoint.y+curPoint.y);
    return temp;
}
void t3()
{
    vector<Point> vp;
    for(int i=0;i<5;++i)
    {
        //Point()
        vp.push_back({1.0*i,2.0*i});
    }
    Point sum=accumulate(vp.begin(),vp.end(),Point(0,0),avage);
    sum.x=sum.x/vp.size();
    sum.y=sum.y/vp.size();

    std::cout<<"x: "<<sum.x<< "  y:  "<<sum.y<<endl;

}
int main()
{
    //t1();
    //t2();
    t3();
    return 0;
}
















