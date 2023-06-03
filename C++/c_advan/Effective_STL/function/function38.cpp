/*条款38：把仿函数类设计为用于值传递*/
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
void qsort(void *base,size_t nmemb,size_t size,int(*cmpfcn)(const void*,const void*));
template<class InputIterator,class Function>
Function for_each(InputIterator first,InputIterator last,Function f);//注意是值传递
//实际上，值传递的情况并不是完全打不破的，因为for_each的调用者在调用点可以显式指定参数类型。
class DoSomething:public unary_function<int,void>{
public:
    DoSomething(){};
    void operator()(int x){
    }
};
void t1()
{
    /*
因为函数对象以值传递和返回，你的任务就是确保当那么传递（也就是拷贝）时你的函数对象行为良好。这
暗示了两个东西。第一，你的函数对象应该很小。否则它们的拷贝会很昂贵。第二，你的函数对象必须单态
（也就是，非多态）——它们不能用虚函数。那是因为派生类对象以值传递代入基类类型的参数会造成切割
问题：在拷贝时，它们的派生部分被删除。
    */
    typedef deque<int>::iterator DequeInIter;
    deque<int> di;
    DoSomething d;
    //for_each<DequeInIter,DoSomething&>(di.begin(),di.end(),d);//编译不过去

}






