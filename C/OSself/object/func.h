#include<stdio.h>
extern "C"
{
    int func(int i)
    {
        printf("%d\n", 2*i);
        return 1;
    }
    int var;
}
