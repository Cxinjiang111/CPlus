#include<iostream>
using namespace std;
template<typename T>
class Rational{
public:
    // Rational(const T& numerator=0,
    //         const T&denominator=1);//已引用的方式
    Rational(const T a1=0,
            const T b1=1):a(a1),b(b1){};//已引用的方式
    const T numerator()const//返回值
    {
        return a;

    }
    const T denominator()const
    {
        return b;
    }
public:
//自己声明的函一个函数 负责让编译器去寻找到它
    friend const Rational operator*(const Rational&lhs,
                                    const Rational&rhs)
                                    {
                                        cout<<"    member function"<<endl;
                                        return Rational(lhs.numerator()*rhs.numerator(),lhs.denominator()*rhs.denominator());                                     
                                    }
    private:
    T a;
    T b;
};

// template<typename T>
// const Rational<T> operator*(const Rational<T>&lhs,
//                             const Rational<T>&rhs)
// {
//     cout<<"non-member function    "<<endl;
//     return Rational(lhs.numerator()*rhs.numerator(),lhs.denominator()*rhs.denominator());               
// }
int main()
{
    Rational<int> onehalf(1,2);//因为当对象oneHalf被声明为一个Rational<int>,class Rational<int>
    //于是被具现出现出来，而作为过程的一部分，friend函数operator*也被自动声明出来。后者身为一个函数
    //而非函数模板，因此编译器也在调用时使用隐式转换函数，这就是混合式调用成功的原因
    Rational<int> result=onehalf*2;
   Rational<int> result2=2*onehalf;//
   
    //输出：member function
    //      member function

    Rational<int> twohalf(2,4);
    Rational<int> result3=twohalf*onehalf;

    return 0;
}
模板可参考这个
https://en.cppreference.com/w/cpp/language/overload_resolution



