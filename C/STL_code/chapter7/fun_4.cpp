//证同元素
/*
//证同函数(identityfunction)。任何数值通过此函数后，不会有任何改变
//此式运用于<stl—set．h>,用来指定RB-tree所需的KeyOfValueop 
//那是因为set元素的键值即实值，所以采用过ientity
*/
template<class T>
struct identity:public unary_function<T,T>
{
    const T& operator()(const T&x)const{return x;}
};
/*
／／选择函数(selection function)：接受一个pair，传回其第一元素
//此式运用于<S七l_rnap.h>，用来指定RB-tree所需的KeyOfValue op
／／由于map系以pair元素的第一元素为其键值，所以采用select1st
*/
template<class Pair>
struct select1st:public unary_function<Pair ,typename Pair::first_type>
{
    const typename Pair::first_type&operator()(const Pair&x)const{
        return x.first;
    }
};

template<class Pair>
struct select1st:public unary_function<Pair ,typename Pair::second_type>
{
    const typename Pair::second_type&operator()(const Pair&x)const{
        return x.second;
    }
};

