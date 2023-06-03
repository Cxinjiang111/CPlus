/*必须返回对象时，别妄想返回其reference
绝不要返回pointer或reference指向一个local stack对象，或返回reference指向一个
heap-allocated对象，或返回pointer或reference指向一个local static对象而有可能
同时需要多个这样的对象，
*/
class Rational1{
public:
    Rational1(int numerator=0,int denominator=1):n(numerator),d(denominator){};
private:
    int n,d;//numerator分子  denominator分母
    friend const Rational1 operator*(const Rational1&lhs,const Rational1&rhs);
    //以返回值的形式返回结果而非引用，如果你不担心该对象的构造和析构成本，
};
class Rational{
public:
    Rational(int numerator=0,int denominator=1):n(numerator),d(denominator){};
    inline friend const Rational operator*(const Rational&lhs,const Rational&rhs);
private:
    int n,d;//numerator分子  denominator分母


};
//那就返回一个对象呗 没有办法了

inline const Rational::Rational operator*(const Rational&lhs,const Rational&rhs)
{
    return Rational(lhs.n*rhs.n,lhs.d*lhs.d);
}