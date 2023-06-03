/*
了解相等和等价的区别
*/
/*
等价是基于在一个有序区间中对象值的相对位置。等价一般在每种标准关联容器（比如，set、multiset、map
和multimap）的一部分——排序顺序方面有意义。两个对象x和y如果在关联容器c的排序顺序中没有哪个排在
另一个之前，那么它们关于c使用的排序顺序有等价的值。这听起来很复杂，但实际上，它不。考虑一下，
举一个例子，一个set<Widget> s。两个Widget w1和w2，如果在s的排序顺序中没有哪个在另一个之前，那么关
于s它们有等价的值。set<Widget>的默认比较函数是less<Widget>，而默认的less<Widget>简单地对Widget调用
operator<，所以w1和w2关于operator<有等价的值如果下面表达式为真：
!(w1<w2)&&(w2<w1)
*/
//關聯式容器
//!c.key_comp()(x,y)&&!c.key_comp()(y,x)
//在c的排序顺序中, 如果x在y之前它非真，同时在c的排序顺序中如果y在x之前它非真
#include<string>
#include<set>
#include<algorithm>
using  namespace std;

bool const ciStringCompare(const string&lhs,const string&rhs)
{

}
struct CIStringCompare:public binary_function<string,string,bool>{
    bool operator()(const string&lhs,const string&rhs)const{
        return ciStringCompare(lhs,rhs);
    }
};
int main()
{
    set<string,CIStringCompare> ciss;
    ciss.insert("person");
    //使用set的成員函數find搜索字符串person
    if(ciss.find("person")!=ciss.end())
    {

    }
    //使用algorithm中的函數即類的非成員函數find 會出問題
    if(find(ciss.begin(),ciss.end(),"peson")!=ciss.end())
    {
        
    }

    return 0;
}

