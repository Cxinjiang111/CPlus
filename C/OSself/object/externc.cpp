#include<stdio.h>
#ifdef __cplusplus
extern "C"{
#endif
    void *memset(void *,int,size_t);
#ifdef __cplusplus
}
#endif 
// if __cplusplus == false
/* void *memset(void *,int,size_t); //C 语言
*/
// if __cplusplus == true
/*
extern "C"{
    void *memset(void *,int,size_t);
}
//C 语言
*/