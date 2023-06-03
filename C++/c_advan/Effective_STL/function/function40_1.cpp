/*问题中的typedef是argument_type、first_argument_type、second_argument_type和result_type，但不是那么直截了当，因为不同类型
仿函数类需要提供那些名字的不同子集。总的来说，除非你在写你自己的适配器（本书没有覆盖的主题），
你才不需要知道任何关于那些typedef的事情。那是因为提供它们的正规方法是从一个基类，或，更精确地
说，一个基结构，继承它们。operator()带一个实参的仿函数类，要继承的结构是std::unary_function。operator
()带有两个实参的仿函数类，要继承的结构是std::binary_function。
好，简单来说，unary_function和binary_function是模板，所以你不能直接继承它们。取而代之的是，你必须从
它们产生的类继承，而那就需要你指定一些类型实参。对于unary_function，你必须指定的是由你的仿函数类
的operator()所带的参数的类型和它的返回类型。对于binary_function，你要指定三个类型：你的operator的第
一个和第二个参数的类型，和你的operator地返回类型。
*/
#include<vector>
#include<algorithm>
#include<iostream>
#include<list>
#include<set>
#include<deque>
#include<string>
#include<iterator>
#include<functional>
using namespace std;
class Widget{

};
template<typename T>
//MeetsThreshold是个类
class MeetsThreshold:public std::unary_function<Widget,bool>{
private:
    const  T threshold;
public:
    MeetsThreshold(const T&threshold);
    bool operator()(const Widget&)const;

};
//WidgetNameCompare 这个是个结构
struct WidgetNameCompare:public binary_function<Widget,Widget,bool>
{
    bool operator()(const Widget&,const Widget&)const;
    /* data */
};
//这里和上面不同的是传递的是指针，而不是引用
struct ptrWidgetNameCompare:public std::binary_function<const Widget*,const Widget*,bool>
{
    bool operator()(const Widget*,const Widget*)const;
};

