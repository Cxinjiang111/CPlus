/*将与参数无关的代码抽离*/
#include<iostream>
template<typename T,std::size_t n>
// T:模板参数   n：非模板参数
class SquareMatrix1{
public:
    void invert();
};
void fun()
{
    SquareMatrix1<int,5> a;
    a.invert();
    SquareMatrix1<int,10> b;
    b.invert();
    //上述两个就第二个参数不同 为了避免重复怎么做呢？
}
template<typename T> //不对矩阵的尺寸参数化，
// T:模板参数  
class SquareMatrixBase{
public:
    void invert(std::size_t matrixSize);
};//所共享的矩阵就这一个
template<typename T,std::size_t n>
class SquareMatrix:private SquareMatrixBase{ 
//这里继承的是private这的base class只是为了帮助derived classes实现，
//不是为了表现SquareMatrix和SquareMatrixBase之间的is-a关系
private:
    using SquareMatrixBase<T>::invert;//企图成为避免derived classes 代码重复
public:
    void invert(){this->invert(n);}//this 内的函数防止被derived class 覆盖掉
//this相当于指向类内部成员，这里显式的不让调用SquareMatrix的成员invert，
//而是类成员SquareMatrixBase中的invert
};
void fun1()
{
    SquareMatrix<int ,5> a;
    a.invert();
}














