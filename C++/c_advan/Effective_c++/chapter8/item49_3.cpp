/*
静态成员是可以独立访问的，也就是说，无须创建任何对象实例就可以访问，而静态成员函数可不建立对象就可以被使用。
  或者说静态函数与一般函数没有太大的区别，只是访问有限制，静态变量跟一般的全局变量的区别就是访问有限制。
*/
#include<iostream>
using namespace std;
class test
{
private:
public:
    static int i;
};
int test::i = 100;//此句包含了声明和赋值，初始化不受private和protected访问限制，但是若是priivate，下面main函数就无法访问
int main()
{
    cout << test::i << endl;
    return 0;
}
/*
好处：用static修饰的成员变量在对象中是不占内存的，因为他不是跟对象一起在堆或者栈中生成，用static修饰的变量在静态存储区生成的，所以用static修饰一方面的好处是可以节省对象的内存空间。
所以一般类const变量一般改为static const变量，可以节省一些空间。
*/
