#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
#include<algorithm>
#include<array>
#include<mutex>
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
        std::lock_guard<std::mutex> g(m);
        if(!rootAreValid){  //// 如果缓存不可⽤
                                //计算rootVals的值，是否计算得看rootAreValid的情况
            rootAreValid=true; //这里改变了rootAreValid如果时false那么计算根，下次便不在计算值。
        }
        return rootVals;
    }
private:
    mutable std::mutex m;
    mutable bool rootAreValid{false};
    mutable RootType rootVals{};
/*
std::mutex m被声明为mutable，因为锁定和解锁它的都是non-const函数。在roots（const成员函
数）中，m将被视为const对象。
值得注意的是，因为std::mutex是⼀种move-only的类型（⼀种可以移动但不能复制的类型），所以
将m添加进多项式中的副作⽤是使它失去了被复制的能⼒。不过，它仍然可以移动。
*/
};
void t1(){
    polynomial p;

    /*------ Thread 1 ------*/
    auto rootsofp=p.roots();
    /*-------- Thread 2 --------*/
    auto valsGivingzero=p.roots();
}
int main(){


    return 0;

}



