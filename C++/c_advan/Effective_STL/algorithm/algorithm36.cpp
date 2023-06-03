/*条款36：了解copy_if的正确实现*/
/*
copy             copy_backward
replace_copy     reverse_copy
replace_copy_if  unique_copy
remove_copy      rotate_copy
remove_copy_if   partial_sort_copy
unintialized_copy
但没有一个是copy_if。这意味着你可以replace_copy_if，你可以remove_copy_if，你可以copy_backward或者
reverse_copy，但如果你只是简单地想要拷贝一个区间中满足某个判断式的元素，你只能自己做。
*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<random>
#include<ctime>
#include<string>
#include<iterator>
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
bool isDefective(const Widget&w)
{

}
//正确的copy_if
template<typename InputIterator,typename OutputIterator,typename Predicate>
OutputIterator copy_if(InputIterator begin,InputIterator end,OutputIterator destBegin,Predicate p)
{
    while (begin!=end)
    {
        if(p(*begin))*destBegin++=*begin;
        ++begin;
    }
    return destBegin;   
}


void t1()
{
    vector<Widget> widgets;
//_OutputIterator  copy_if(_InputIterator __first, _InputIterator __last,_OutputIterator __result, _Predicate __pred)
    //copy_if(widgets.begin(),widgets.end(),ostream_iterator<Widget>(cerr,"\n"),isDefective);
}





