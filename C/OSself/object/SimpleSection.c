#include<stdio.h>        //File Header
int global_init_var=84; //.text section
int global_uninit_var; //.bss section
void func1(int i)//.text section
{
    printf("%d\n",i);
}
int main()//.text section
{
    static int static_var=85;//.text section
    static int static_var2;//.bss section 
    int a=1;
    int b;    //未知值
    func1(static_var+static_var2+a+b);
    return 0;
}











