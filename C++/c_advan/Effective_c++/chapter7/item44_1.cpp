/*
SquareMatrixBase存储一个指针，指向矩阵数值所在的内存。
只要它存储了那些东西，也就可能存储矩阵尺寸
*/
#include<iostream>
#include<memory>
template<typename T>
class SquareMatrixBase{
protected:
    SquareMatrixBase(std::size_t n,T*pMem):size(n),pData(pMem){};
    void setDataPtr(T*ptr){pData=ptr;}//送出矩阵大小和数据指针给 base class
private:
    std::size_t size;
    T* pData;
};
template<typename T,std::size_t n>
class SquareMatrix:private SquareMatrixBase<T>{
public:
    SquareMatrix():SquareMatrixBase<T>(n,data){}
private:
    T data[n*n];
};
template<typename T,std::size_t n>
class SquareMatrix:private SquareMatrixBase<T>{
public:
    SquareMatrix():SquareMatrixBase<T>(n,0),pData(new T[n*n]){this->setDataPtr(pData.get());}
private:
   std::shared_ptr<T> data;//指向基类的数据内存的指针，每个继承类都有取得数据的办法
};





