#include<algorithm>
#include<iostream>
#include<list>
#include<deque>
#include<iterator>
using namespace std;
class Widget{
public:
    Widget(int num_):num(num_){}
    void redraw(){
        num=num*2;
    }
    void print()
    {
        cout<<num<<"\t";
    }
    int num;
};
void t1()
{
    list<Widget> lw{Widget(2),Widget(3),Widget(5)};
    //Widget w1(2);
    //lw.push_back(w1(2));
    // for (list<Widget>::iterator it=lw.begin(),it!=lw.end();++it)
    // {
    //     it->redraw();
    // }
    //for_each(lw.begin(),lw.end(),mem_fun_ref(&Widget::redraw));//redraw 可能是全域的，也可能类中，所以这里需要加 Widget域名
    //for_each(lw.begin(),lw.end(),mem_fun_ref(&Widget::print));
    for (list<Widget>::iterator it=lw.begin();it!=lw.end();++it)
    {
        cout<<it->num<<"\t";
    }
}
/*
● 效率：算法通常比程序员产生的循环更高效。
● 正确性：写循环时比调用算法更容易产生错误。
● 可维护性：算法通常使代码比相应的显式循环更干净、更直观。
公平的说，STL的实现者知道begin和end（以及类似的函数，比如size）用得很频繁，所以他们尽可能把它们
实现得最高效。几乎肯定会inline它们，并努力编码使得绝大部分编译器都可以通过将计算结果提到循环外
（译注：频度优化的一种）来避免重复计算。然而，经验表明，这样的实现不是总可以成功的，而且当不成
功时，对重复计算的避免足以让算法比手写的循环具有性能优势。
*/
void t2()
{
    int maxNumDoubles=10;
    double data[maxNumDoubles]={9,8,7,6,5,4,3,2,1,0};

    deque<double> d{1,2,3,4,5,6};
    int numDoubles=6;
    deque<double>::iterator insertLocation=d.begin();
    for (size_t i = 0; i < numDoubles; i++)//numDoubles你要插入的个数
    {  
        //insertLocation迭代器的位置 
        insertLocation=d.insert(insertLocation,data[i]+4);
        ++insertLocation;//更新迭代器的位置
    }
    //13      12      11      10      9       8       1       2       3       4       5       6 
    /*
template<typename _InputIterator, typename _OutputIterator, typename _UnaryOperation>
_OutputIterator transform(_InputIterator __first, _InputIterator __last,
                        _OutputIterator __result,_UnaryOperation __unary_op)
    */
    transform(data,data+numDoubles,inserter(d,d.begin()),bind2nd(plus<double>(),4));
    for (auto &&i : d)
    {
        cout<<i<<"\t";
    }
}
template<typename T>
class BetweenValues:public unary_function<T,bool>{
public:
    BetweenValues(const T&lowValue,const T&highValue):lowVal(lowValue),highVal(highValue){}
    bool operator()(const T Val)
    {
        return val>lowVal&&val<highVal;
    }
private:
    T lowVal;
    T highVal;
};
void t3()
{
    vector<int> v;
    vector<int>::iterator i=find_if(v.begin(),v.end(),BetweenValues<int>(10,20));
}
int main()
{
    //t1();
    t2();
    return 0;
}






