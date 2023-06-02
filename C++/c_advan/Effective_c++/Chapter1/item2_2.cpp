#include<iostream>
using namespace std;
int f(int a)
{
    cout<<a<<endl;
    return a;
}
#define CALL_WITH_MAX(a,b) f((a)>=(b)?(a):(b))
template<typename T>
inline void CALL_WITH_MAX_1(const T a,const T b)
{
    f(a>b?a:b);
}
int main()
{
    int a=5,b=0;
    int c=5,d=0;
    CALL_WITH_MAX(++a,b);//a被累加两次   7累加两次
    CALL_WITH_MAX_1(++c,d);//           6 累加一次 推荐用函数inline 代替宏

    //CALL_WITH_MAX(++c,d+6);//a被累加一次
    //这里，调用f之前，a的递增次数竟然取决于它被拿来和谁比较 这个底层不太了解，只是不建议用宏取写函数




    return 0;
}


