/*条款31：了解你的排序选择*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<string>
using namespace std;
class Widget{
public:
    Widget();
    ~Widget();
    Widget(int n1,double s1):num(n1),d(s1){};
    void setValue(int n1,double s1);
    int num;
    double d;
};
Widget::Widget(){}
Widget::~Widget(){}
void Widget::setValue(int n1,double s1)
{
    this->num=n1;
    this->d=s1;
}
bool qualityCompare(const Widget&lhs,const Widget &rhs)
{
    if(lhs.num<rhs.num)
        return true;
    else
        return false;

}
void print(const vector<Widget>& w1)
{
    //这种排完序的前5个是有序的，后面的无序
    for(auto &it:w1)
    {
        cout<<it.num<<"  d   "<<it.d<<endl;
    }
}
/*
调用完partial_sort后，widgets的前20个元素是容器中最好的而且它们按顺序排列，也就是，质量最高的Widget
是widgets[0]，第二高的是widgets[1]等。这就是你很容易把最好的Widget发送给你最好的客户，第二好的
Widget给你第二好的客户等。
*/
void t1()
{
    vector<Widget> w1;
    unsigned seed=time(0);
    srand(seed);
    for(int i=0;i<10;++i)
    {
        Widget t1(random(),20-i);
        w1.push_back(t1);
    }                                                                                                
    //partial_sort(_RandomAccessIterator __first,_RandomAccessIterator __middle,_RandomAccessIterator __last, _Compare __comp)
    partial_sort(w1.begin(),w1.end()+5,w1.end(),qualityCompare);
    //这种排完序的前5个是有序的，后面的无序
}
/*
如果你关心的只是能把20个最好的Widget给你的20个最好的客户，但你不关心哪个Widget给哪个客户，
partial_sort就给了你多于需要的东西。在那种情况下，你需要的只是任意顺序的20个最好的Widget。STL有一
个算法精确的完成了你需要的，虽然名字不大可能从你的脑中迸出。它叫做nth_element。

nth_element排序一个区间，在ri位置（你指定的）的元素是如果区间被完全排序后会出现在那儿的元素。另
外，当nth_element返回时，在n以上的元素没有在排序顺序上在位置n的元素之后的，而且在n以下的元素没
有在排序顺序上在位置n的元素之前的。如果这听起来很复杂，那只是因为我必须仔细地选择我的语言。一
会儿我会解释为什么，但首先让我们看看怎么使用nth_element来保证最好的20个Widget在widgets vector的前
端：
*/
void init(vector<Widget>& vw1)
{

    Widget w1(1,100);
    vw1.push_back(w1);
    w1.setValue(2,99);
    vw1.push_back(w1); 
    w1.setValue(8,88);
    vw1.push_back(w1); 
    w1.setValue(7,101);
    vw1.push_back(w1); 

    w1.setValue(6,62);
    vw1.push_back(w1); 
    w1.setValue(4,78);
    vw1.push_back(w1); 
    w1.setValue(10,98);
    vw1.push_back(w1); 

    w1.setValue(5,95);
    vw1.push_back(w1); 
    w1.setValue(11,97);
    vw1.push_back(w1); 
}
void t2()
{    
    vector<Widget> vw1;
    init(vw1);
    nth_element(vw1.begin(),vw1.begin()+5,vw1.end(),qualityCompare);
    print(vw1);
    /*
 6  d   62
2  d   99
5  d   95
4  d   78
1  d   100
前面的是乱序的 但是是前五个最小的 应该是大根堆的排序，预先队列
7  d   101
8  d   88
10  d   98
11  d   97
    */

   /*
   
   */
}
/*
现在谈谈nth_element，这个名字奇怪的算法是个引人注目的多面手。除了能帮你找到区间顶部的n个元素，
它也可以用于找到区间的中值或者找到在指定百分点的元素：
*/
void t3()
{
    vector<Widget> vw1;
    vector<Widget>::iterator begin(vw1.begin());
    vector<Widget>::iterator end(vw1.end());
    
    init(vw1);
    vector<Widget>::iterator goalPosition;
    goalPosition=vw1.begin()+vw1.size()/2;
    nth_element(begin,goalPosition,end,qualityCompare);
    vector<Widget>::size_type goalOffset=0.25*vw1.size();//按照一定的偏移量
    nth_element(begin,begin+goalOffset,end,qualityCompare); 

}
/*
比如假设，你不需要鉴别出20个质量最高的Widget。取而代之的是，你需要鉴别出所有质量等级为1或2
的。当然你可以按照质量排序这个vector，然后搜索第一个质量等级比2差的。那就可以鉴别出质量差的
Widget的区间起点。
但是完全排序需要很多工作，而且对于这个任务做了很多不必要的工作。一个更好的策略是使用partition算
法，它重排区间中的元素以使所有满足某个标准的元素都在区间的开头。
*/
bool hasAcceptQuality(const Widget&w)
{
    if(w.num<6)
        return true;
    else
        return false;
}
void t4()
{
    vector<Widget> vw1;
    init(vw1);
    vector<Widget>::iterator begin(vw1.begin());
    vector<Widget>::iterator end(vw1.end());
    

    vector<Widget>::iterator goodEnd=partition(begin,end,hasAcceptQuality);
    cout<<(*goodEnd).d<<endl;
    cout<<"=========="<<endl;
    print(vw1);
    /*
1  d   100
2  d   99
5  d   95
4  d   78
6  d   62
7  d   101
10  d   98
8  d   88
11  d   97
    */
}
int main()
{                                                                                           

    t4();
    return 0;

}




