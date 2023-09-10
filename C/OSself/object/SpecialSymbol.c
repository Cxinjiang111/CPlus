#include<stdio.h>
//特殊符号
extern char __executable_start[];
extern char etext[],_exext[],__exext[];
extern char edata[],_edata[];
extern char end[],_end[];
int main()
{
    printf("Exectutable  Start %p \n",__executable_start);
    //printf("Text End %p %p %p\n",etext,_exext,__exext);
    printf("Data End %p %p \n",edata,_edata);
    printf("Exectutable End %p %p\n",end,_end);
    return 0;
}