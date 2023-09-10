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
    func1(b);//.text section
    func1(global_uninit_var);//.text section
    func1(static_var2);//.text section

    /*
    output 
    22095
    0
    0
    */
    return 0;
}