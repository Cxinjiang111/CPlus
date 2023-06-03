/*永远让比较函数对相等的值返回false
*/
#include<set>
#include<iostream>
#include<string>
using namespace std;
struct StringPtrGreater:public binary_function<const string*,const string*,bool>{
    bool operator()(const string*ps1,const string*ps2)
    {
        return !(*ps1<*ps2);//這個東西的就是*ps1>=*ps2 這種比較就會出問題
       // return *ps1>*ps2;//這個就ok
    }
};



int main()
{
    set<int,less_equal<int>> s;
    s.insert(10);
    s.insert(10);

    for (auto &i : s)
    {
        cout<<i<<endl;
    }
  //output   10  10  
/*
set遍历它的内部数据结构以查找哪儿适合插入10B。最终，它总要检查10B是否与10A相同。关联容器对“相
同”的定义是等价（参见条款19），因此set测试10B是否等价于10A。当执行这个测试时，它自然是使用set的
比较函数。在这一例子里，是operator<=，因为我们指定set的比较函数为less_equal，而less_equal意思就是
operator<=。于是，set将计算这个表达式是否为真：
!(10A <= 10B) && !(10B <= 10A) // 测试10A和10B是否等价
!(true) && !(true)
false && false
结果当然是false。 也就是说，set得出的结论是10A与10B不等价，因此不一样，于是它将10B插入容器中10A的
旁边。在技术上而言，这个做法导致未定义的行为，但是通常的结果是set以拥有了两个为10的值的拷贝而告
终，也就是说它不再是一个set了。通过使用less_equal作为我们的比较类型，我们破坏了容器！此外，任何对
相等的值返回true的比较函数都会做同样的事情。

*/
    return 0;
}