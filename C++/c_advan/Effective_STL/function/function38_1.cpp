/*带着你要放进你的仿函数类的数据和/或多态，把它们移到另一个类中。然后给你的仿函数一个指
向这个新类的指针。
*/
#include<numeric>
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<set>
#include<deque>
#include<string>
#include<iterator>
using namespace std;
class Widget{

};
template<typename T>
class BPFC:public unary_function<T,void>
{
private:
    BPFCImpl<T>*pImpl;//组合的形式
    // Widget w;//这个类中有很多数据
    // int x;
public:
    void operator()(const T &val)const//现在是非虚函数 调用BPFCImpl
    {
        pImpl->operator()(val);
    }
};
template<typename T>
class BPFCImpl:public unary_function<T,void>{
private:
    Widget w;//以前在BPFC里的所有数据 现在在这里
    int x;
    virtual ~BPFCImpl();//多态需要虚析构函数

    virtual void operator()(const T&val)const;
    friend class BPFC<T>;//让BPFC可以访问这些数据
};












