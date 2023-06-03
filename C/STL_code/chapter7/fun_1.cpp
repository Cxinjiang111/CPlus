/* 任何应用程序欲使用STL内建的仿函数，都必须含<functional>头文件 
仿函数扮演者策略角色。


*/
template<class Arg,class Result>
struct unary_function
{
    typedef Arg argument_type;
    typedef Result result_type;
};
//一旦某个仿函数继承了unary_function,其用户便可这样该仿函数的参数型别。并已相同手法取得其返回值型别
template <class T>
struct negate:public unary_function<T,T>
{
    T operator()(const T &x)const{ return -x;}
};
//Predicate 传入的类型必须是unary_function类型
template <class Predicate>
class unary_negate{
public:
    bool operator()(const typename Predicate::argument_type&x)const{
    }
};
