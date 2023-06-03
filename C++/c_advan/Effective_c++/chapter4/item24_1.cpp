class Rational{
public:
    Rational (int numerator=0,int denominator=1);
   //explicit Rational (int numerator=0,int denominator=1);
    int numerator()const;
    int denomiantor()const;
     const Rational operator*(const  Rational&rhs)const;
private:
    int numerator;
    int denominator;
};
const Rational operator*(const Rational &lhs,const Rational&rhs)
{
    return Rational(lhs.numerator()*rhs.numerator());
}
void f()
{
    Rational oneFourth(1,4);
    Rational result;
    result=oneFourth*2;
    result=2*oneFourth;
}