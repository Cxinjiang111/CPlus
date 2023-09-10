// #include<stdio.h>
// extern int ext;
// int weak;
// int strong =1;
// __attribute__((weak)) weak2=2;
// int main()
// {
//     int strong = 5;
//     printf("%d\n", strong);
//     return 0;
// }
//这里还是有点不懂？？？ 
#include <stdio.h>
#include <pthread.h>
int pthread_create (pthread_t *__restrict __newthread,
			   const pthread_attr_t *__restrict __attr,
			   void *(*__start_routine) (void *),
			   void *__restrict __arg) __attribute__((weak));

// int pthread_create(
//     pthread_t*,
//     const pthread_attr_t*,
//     void *(*)(void*),
//     void*
// ) 
// {
//     return 0;
// }
int main()
{
    if(pthread_create==0)
    {
        printf("this is multi-thread version\n");
    }
    else
    {
        printf("this is single-thread version\n");
    }
}

int pthread_create (pthread_t *__restrict __newthread,
			   const pthread_attr_t *__restrict __attr,
			   void *(*__start_routine) (void *),
			   void *__restrict __arg) 
               {
                return 1;
               }
