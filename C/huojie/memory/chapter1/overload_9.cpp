#include<iostream>
#include<malloc.h>
using namespace std;
class Foo{
public:
//这个必须为static 不需要申请Foo对象也可调用malloc函数申请内存
static void *operator new(size_t num){
        return malloc(num);
    }
static void operator delete(void *p,size_t)
    {
        free(p);
    }
public:
int num1;
int num2;
};
int main()
{
    Foo *p=new Foo();
    p->num1=1;

    return 0;
}
