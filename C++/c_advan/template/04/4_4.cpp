//相关型别 指的是其引数与返回值的型别，Generator具有一个相关型别（即其返回型别），
//Unary function具有两个相关型别（即其引数型别与返回型别）
//函数对象可以被定义为class，所以就像iterator一样，他们可以拥有嵌套型别，
//空的基类型别
template<class Arg,class Result>
struct unary_function{
    typedef Arg     argument_type;
    typedef Result  result_type;
};
template<class Arg1,class Arg2,class Result>
struct binary_class{
    typedef Arg1        first_argument_type;
    typedef Arg2        second_argument_type;
    typedef Result      result_type;
};
//修改even<T>的方式有二，一是明白声明出两个相关型别，要不就更简单的继承unary_function
template<class Number>
struct even:public unary_function<Number,bool>
{
    bool operator()(Number x)const {return (x&1)==0;}
};
//这不是完美的解决方案，因为他不能适用于一种很重要函数对象身上：函数指针，函数指针是内建型别，不是class ，所以无法为他定义嵌套型别
//许多运用了函数对象的算法，并不会明白取用其引数型别于返回型别，所以没有必要对每一个函数对象都提供那些型别的取用方法，
/*
STL会把函数对象和adaptable函数对象区分开来，一般而言，一个函数对象会有一个引数（参数）型别与一个返回型别，但程序不需要
知道那些型别名称，至于adaptable函数对象则会指明引数与返回型别为何，他会内含嵌套的typedef
*/





