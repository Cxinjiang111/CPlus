//投射函数：传回第一参数，忽略第二参数'
template<class Arg1,class Arg2>
struct project1st:public binary_function<Arg1,Arg2>
{
    Arg1 operator()(const Arg1 &x,const Arg2 &y)const{
        return x;
    }
};

//投射函数：传回第2参数，忽略第1参数'
template<class Arg1,class Arg2>
struct project1st:public binary_function<Arg1,Arg2>
{
    Arg1 operator()(const Arg1 &x,const Arg2 &y)const{
        return y;
    }
};