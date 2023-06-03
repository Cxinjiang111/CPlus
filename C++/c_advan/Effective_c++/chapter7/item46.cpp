/*需要类型转换时轻微模板定义非成员函数*/
template<typename T>
class Rational{
public:
    Rational(T& a,T& b):numerator(a),denominator(b){};
    Rational(const T& n,
            const T&d):(numerator(n),denominator(d){};//已引用的方式
    const T numerator1()const;//返回值
    const T denominator1()const;
private:
    int   numerator;
    int denominator;
};
template<typename T>
const Rational<T> operator*(const Rational<T>&lhs,
                            const Rational<T>&rhs)
{
}

void f()
{
    Rational<int> onehalf(1,2);
    //Rational<int> result=onehalf*2;
    Rational<int> result=Rational(2,1)*onehalf;//
    
}





