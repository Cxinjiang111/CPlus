//binary_function
template<class Arg1,class Arg2,class Result>
struct binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type; 
    typedef Result result_type;
};
//以下仿函数继承了binary_function
template<class Operation>
class binder1st{
    protected:
        Operation op;
        typename Operation::first_argument_type operator()(const  typename Operation::second_argument_type&x)const{    
        }
};
