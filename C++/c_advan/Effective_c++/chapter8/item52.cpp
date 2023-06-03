/*写了placement new也要写placement delete


*/
/*
成员函数的名称会掩盖其外围作用域的相同名称，避免让class专属的new掩盖客户期望的其他new

*/
#include<iostream>
class Base{
public:
    //这个new 会遮掩正常的global形式
    static void*operator new(std::size_t size,std::ostream&logStream)throw();

};
class Derived:public Base{//
public:
    static void*operator new(std::size_t size)throw();//重新声明正常的形式的new 就会掩盖掉基类中的operator new
};
int main()
{
    //Base *p=new Base;//由于全局的被掩盖了，所以不能用
    Base *p=new(std::cerr) Base;//这个才会调用Base中的operator new
    Derived *p =new Derived;//ok 
    //Derived *p=new(std::cerr) Derived;//error;
    return 0;
}
/*
这种掩盖问题的函数如下
void *operator new(std::size_t)throw(std::bad_alloc);
void *operator new(std::size_t,void*)throw();
void *operator new(std::size_t,const std::nothrow_t&)throw();
*/









