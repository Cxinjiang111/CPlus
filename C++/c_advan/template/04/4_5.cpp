//函数对象适配器
//适配器将一种将某接口转换成另一种接口的组件，
//比如反向迭代器 为了避免重复撰写代码，可以重复运用代码
template<class AdaptablePredicate>
class unary_negate{
private:
    AdaptablePredicate pred;
public:
    typedef typename AdaptablePredicate::argument_type argument_type;
    typedef typename AdaptablePredicate::result_type    result_type;
    unary_negate(const AdaptablePredicate &x):pred(x){}
    bool operator()(const argument_type&x)const{
        return !pred(x);//这个函数是复用了
    }
};
//unary_negate<F>(f); 是f之反相的一个predicate
//unary_negate adapter的唯一问题是表达式unary_negate<F>(f)没必要如此累赘，我们可以定义一个小的辅助函数unary_negate 对象的产生
template<class AdaptablePredicate>
inline unary_negate<AdaptablePredicate> notl(const AdaptablePredicate &pred)
{
    return unary_negate<AdaptablePredicate>(pred);
}
//find_if(first,last,notl(event<int>()));
//如果需要将一般函数指针传递给函数对象适配器，可以利用pointer_to_unary_function将函数指针转换为Adaptable Unary Function 
template<class Arg,class Result>
struct unary_function{
    typedef Arg     argument_type;
    typedef Result  result_type;
};
template<class Arg,class Result>
class Pointer_to_unary_function:public unary_function<Arg,Result>
{
private:
    Result  (*ptr)(Arg);//函数指针
public:
    Pointer_to_unary_function(){}
    Pointer_to_unary_function(Result (*x)(Arg)):ptr(x){}
    Result operator()(Arg x)const {result ptr(x);}//将参数Arg转换了函数指针
};
template<class Arg,class Result>
inline Pointer_to_unary_function<Arg,Result> ptr_fun(Result (*x)(Arg))//Result (*x)(Arg)构建函数指针
{
    return Pointer_to_unary_function<Arg,Result>(x);
}




