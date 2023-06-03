/*条款46：考虑使用函数对象代替函数作算法的参数

*/
#include<algorithm>
#include<iostream>
#include<list>
#include<deque>
#include<iterator>
#include<set>
using namespace std;
void t1()
{
    vector<int>v;
    sort(v.begin(),v.end(),greater<int>());
}
/*
如果你注意了抽象惩罚，你可能决定避开函数对象而使用真的函数，一个不光是真的，而且是内联的函数：
*/
inline bool IntGreater(int  lhs,int rhs)
{
    return lhs>rhs;
}
void t2()
{
    vector<int>v;
    sort(v.begin(),v.end(),IntGreater);
    //sort(vector<int>::iterator first,vector<int>::iterator last,bool(*comp)(int ,int));  
    /*
    因为comp是一个指向函数的指针，每次在sort中用到时，编译器产生一个间接函数调用——通过指针调用。
大部分编译器不会试图去内联通过函数指针调用的函数，甚至，正如本例中，那个函数已经声明为inline而且
这个优化看起来很直接。为什么不？可能因为编译器厂商从来没有觉得值得实现这个优化。你得稍微同情一
下编译器厂商。他们有很多需求，而他们不能做每一件事。你的需要并不能让他们实现那个优化。
 把函数指针作为参数会抑制内联的事实解释了一个长期使用C的程序员经常发现却难以相信的现象：在速度
上，C++的sort实际上总是使C的qsort感到窘迫。当然，C++有函数、实例化的类模板和看起来很有趣的
operator()函数需要调用，而C只是进行简单的函数调用，但所有的C++“开销”都在编译期被吸收。在运行
期，sort内联调用它的比较函数（假设比较函数已经被声明为inline而且它的函数体在编译期可以得到）而
qsort通过一个指针调用它的比较函数。结果是sort运行得更快。   */
}
/*
有趣的是，如果你比较了两个sort调用（一个使用greater<double>，一个使用doubleGreater）的性能，你基本
上可以明确地知道使用greater<double>的那个更快。实际来说，我在四个不同的STL平台上测量了对一百万个
double的vector的两个sort调用，每个都设为针对速度优化，使用greater<double>的版本每次都比较快。最差的
情况下，快50%，最好的快了160%。抽象惩罚真多啊。
这个行为的解释很简单：内联。如果一个函数对象的operator()函数被声明为内联（不管显式地通过inline或者
隐式地通过定义在它的类定义中），编译器就可以获得那个函数的函数体，而且大部分编译器喜欢在调用算
法的模板实例化时内联那个函数。在上面的例子中，greater<double>::operator()是一个内联函数，所以编译器
在实例化sort时内联展开它。结果，sort没有包含一次函数调用，而且编译器可以对这个没有调用操作的代码
进行其他情况下不经常进行的优化。
*/
void t3()
{
    set<string> s;
    s.insert("hello");
    s.insert("world");
    s.insert("my");
    s.insert("name");
    vector<int> v;
    v.resize(10);
    transform(s.begin(),s.end(),ostream_iterator<string::size_type>(cout,"\n"),mem_fun_ref(&string::size));
    transform(s.begin(),s.end(),v.begin(),mem_fun_ref(&string::size));
    //目前没有问题 可能存在兼容性的问题
    for_each(v.begin(),v.end(),[&](int i){cout<<i<<"\t";});
}
//构建仿函数
struct StringSize:public unary_function<string,string::size_type>
{
    string::size_type operator()(const string&s)const{
        return s.size();
    }
};
//构建普通函数
string::size_type StringSIZE(const string&s)
{
    return s.size();
}
void t4()
{
    set<string> s;
    s.insert("hello");
    s.insert("world");
    s.insert("my");
    s.insert("name");
    vector<int> v;
    v.resize(10);
    //使用仿函数的形式可以避免有平台 编译器带来的问题
    //transform(s.begin(),s.end(),ostream_iterator<string::size_type>(cout,"\n"),StringSize());
    transform(s.begin(),s.end(),ostream_iterator<string::size_type>(cout,"\n"),StringSIZE);
    //transform(s.begin(),s.end(),v.begin(),mem_fun_ref(&string::size));
    //目前没有问题 可能存在兼容性的问题
    //for_each(v.begin(),v.end(),[&](int i){cout<<i<<"\t";});
} 

template<typename InputIter1,typename InputIter2>
void writeAverage(InputIter1 begin1,InputIter1 end1,InputIter2 begin2,InputIter2 end2,ostream& s)
{

    transform(begin1,end1,begin2,ostream_iterator<typename iterator_traits<InputIter1>::value_type>(s,"\n"),
                                average<typename iterator_traits<InputIter1>::value_type>);


}
/*
很多编译器接受这段代码，但是C++标准倾向于禁止它。理由是理论上有可能存在另一带有一个类型参数的
函数模板叫做average。如果有，表达式average<typename iterator_traits<lnputIter1>::value_type>将是模棱两可
的，因为它不清楚将实例化哪个模板。在这个特殊的例子里，不存在模棱两可，但是无论如何，有些编译器
会拒绝这段代码，而且那么做是允许的。没有关系。解决这个问题的方法是依靠一个函数对象：
*/
template<typename InputIter1,typename InputIter2>
void writeAverage(InputIter1 begin1,InputIter1 end1,InputIter2 begin2,InputIter2 end2,ostream& s)
{

    transform(begin1,end1,begin2,ostream_iterator<typename iterator_traits<InputIter1>::value_type>(s,"\n"),
                                average<typename iterator_traits<InputIter1>::value_type>());


}
//改成仿函数的形式
template<typename FPType>
struct AVERAGE : public binary_function<FPType,FPType,FPType>{
    FPType operator()(FPType val1,FPType val2)
    {
        return (val1+val2)/2;
    }
};
template<typename InputIter1,typename InputIter2>
void writeAverage_1(InputIter1 begin1,InputIter1 end1,InputIter2 begin2,InputIter2 end2)
{

    transform(begin1,end1,begin2,ostream_iterator<typename iterator_traits<InputIter1>::value_type>(cout,"\n"),
                                AVERAGE());


}
void t5()
{
    vector<int> s1{1,2,3,4,5};
    vector<int> s2{6,7,8,9,10};
    writeAverage_1(s1.begin(),s1.end(),s2.begin(),s2.end());
}

int main()
{
    t4();
    return 0;
}






