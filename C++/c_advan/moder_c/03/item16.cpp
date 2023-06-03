#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
#include<algorithm>
#include<array>
using namespace std;
/*
计算多项式的根是很复杂的，因此如果不需要的话，我们就不做。如果必须做，我们肯定不会只做⼀
次。所以，如果必须计算它们，就缓存多项式的根，然后实现roots来返回缓存的值。下⾯是最基本的
实现：
*/
class polynomial{
public:
    using RootType=std::vector<double>;
    RootType roots()const{ 
        if(!rootAreValid){  //// 如果缓存不可⽤
                                //计算rootVals的值，是否计算得看rootAreValid的情况
            rootAreValid=true; //这里改变了rootAreValid如果时false那么计算根，下次便不在计算值。
        }
        return rootVals;
    }
private:
    mutable bool rootAreValid{false};
    mutable RootType rootVals{};
    /*
从概念上讲，roots并不改变它所操作的多项式对象。但是作为缓存的⼀部分，它也许会改变
rootVals和rootsAreVaild的值。这就是mutable的经典使⽤样例，这也是为什么它是数据成员声明的⼀部分。
    */
};
void t1(){
    polynomial p;

    /*------ Thread 1 ------*/
    auto rootsofp=p.roots();
    /*-------- Thread 2 --------*/
    auto valsGivingzero=p.roots();
/*
这些⽤⼾代码是⾮常合理的。roots是const 成员函数，那就表⽰着它是⼀个读操作。在没有同步的情
况下，让多个线程执⾏读操作是安全的。它最起码应该做到这点。在本例中却没有做到线程安全。因为
在roots中，这些线程中的⼀个或两个可能尝试修改成员变量rootsAreVaild和rootVals。这就意味
着在没有同步的情况下，这些代码会有不同的线程读写相同的内存，这就是data race的定义。这段代
码的⾏为是未定义的

*/
}
int main(){


    return 0;

}



