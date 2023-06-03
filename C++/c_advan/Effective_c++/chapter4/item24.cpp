/*若所有参数皆需类型转换，请为此采用non-menber函数
*/
class Rational{
public:
    Rational (int numerator=0,int denominator=1);
   //explicit Rational (int numerator=0,int denominator=1);
    int numerator()const;
    int denomiantor()const;
     const Rational operator*(const  Rational&rhs)const;
};
int main()
{
    Rational oneEight(1,8);
    Rational oneHalf(1,2);
    Rational result=oneHalf*oneEight;
    result=result*oneEight;
    //混合运算
    result=oneHalf*2;//ok
    //result=2*oneHalf;//error  
    //当你以对应的函数形式重写上述两个式子，
    result= result.operator*(2);
   // result=2.operator*(oneHalf);//error 这里并不存在int的operator*
/*
再次看看先前成功的那个调用。注意其第二参数是整数 2' 但Rational::operator＊需要的实参却是个Rational对象。
这里发生了什么事？为什么2在这里可被接受， 在另一个调用中却不被接受？
因为这里发生了所谓隐式类型转换(implicit type conversion)。编译器知道你正在 传递一个int, 
而函数需要的是Rational;但它也知道只要调用Ra巨onal构造函数 并赋予你所提供的int，就可以变出一个适当的Rational来。 
于是它就那样做了。换 句话说此一调用动作在编译器眼中有点像这样：
*/
const Rational temp(2);
result=oneHalf*temp;
/*
当然， 只因为涉及non-explicit构造函数， 编译器才会这样做。 如果Rational 构造函数是explicit, 以下语句没有一个可通过编译：
然而你的目标不仅在一致性， 也要支持混合式算术运算， 也就是希望有个设计能 让以上语句通过编译。
这把我们带回到上述两个语句， 为什么即使Rational构造函数不是explicit, 仍然只有一个可通过编译， 另一个不可以：
result= oneHalf * 2; 
result= 2 * oneHalf;
结论是，只有当参数被列千参数列(parameter list)内，这个参数才是隐式类型转
换的合格参与者。地位相当于 “被调用之成员函数所隶属的那个对象”——即this对象--那个隐喻参数，
绝不是隐式转换的合格参与者。 这就是为什么上述第一次调用可通过编译，
第二次调用则否， 因为第一次调用伴随一个放在参数列内的参数，第二次调用则否。
然而你一定也会想要支持混合式算术运算。可行之道终千拨云见日：
让operator* 成为一个non-member函数，俾允许编译器在每一个实参身上执行隐式类型转换：
*/
}
