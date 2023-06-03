/*条款41：了解使用ptr_fun、mem_fun和mem_fun_ref的原因*/
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
// class Widget{

// };
// void test(Widget&w);
// void t1()
// {
//     vector<Widget> vw;
//     for_each(vw.begin(),vw.end(),test);
// }

class Widget{
    public:
    void test();//成员函数
};
void t2()
{
    vector<Widget> vw;
    for_each(vw.begin(),vw.end(),&Widget::test);
    /*
    error: must use ‘.*’ or ‘->*’ to call pointer-to-member function in ‘__f (...)’, e.g. ‘(... ->* __f) (...)’
    _f(*__first);
 */
}
void t2()
{
    vector<Widget> vw;
    for_each(vw.begin(),vw.end(),mem_fun(Widget::test));
}
void t2()
{
    vector<Widget*> vw;
    for_each(vw.begin(),vw.end(),mem_fun(&Widget::test));
}
/*他们是个类函数模板
template<typename R,typename C>
mem_fun_t<R,C>
mem_fun(R(C::*pmf)());
*/
int main()
{
    t2();


    return 0;
}

