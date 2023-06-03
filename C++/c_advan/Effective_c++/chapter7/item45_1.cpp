/*这样的模板是所谓member function template 其作用是为class生成函数
*/
#include<memory>
#include<iostream>
template<typename T>
class SmatrPtr{
public:
    template<typename U>
    //为了生成copy构造函数
    SmatrPtr(const SmatrPtr<U>&other):heldPtr(other.get()){}
    T*get()const{return heldPtr;}
private:
    T* heldPtr;
};
template<typename T>
class Top{
    Top(){};
    public:
        virtual void print();
};
template<typename T>
void Top<T>::print()
{
    std::cout<<"Top::print()"<<std::endl;
}
template<typename T>
class Middle:public Top{
public:
    Middle();
    virtual void print();
};
template<typename T>
void Middle<T>::print()
{
    std::cout<<"Middle::print()"<<std::endl;
}
/*
对任何类型T和任何类型U，这里可以根据SmartPtr<U>生成一个SmartPtr<T>
*/
void fun()
{
    //这个怎么去用呀
    //Top* tp=new Middle();
    
    //SmatrPtr<Top> tpp(tp);
    //std::shared_ptr<Top> p1=std::make_shared<Middle>(new Middle);
    //error
    //std::shared_ptr<Top<int> > p1 = std::make_shared<Middle<int>>(std::make_shared<Middle>(new Middle));
}
int main()
{
    fun();
    return 0;
}







