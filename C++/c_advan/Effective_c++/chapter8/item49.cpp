/*了解new-handler的行为*/
#include<errno.h>
#include<cerrno>
#include<error.h>

namespace std{
    typedef void (*new_handler)();//指针函数
    new_handler set_new_handler(new_handler p)throw();//传入一个指针函数，传出指针函数
    //上面这个函数在内存分配失败时，给出一个指针p 执行set_new_handler异常处理函数
    //参数new_handler p指向operator new无法分配足够内存时该被调用的函数
    //返回值也是个指针，指向set_new_handler被调用前正在被执行的那个new-handler函数
}
void outofMem()
{
    std::cerr<<"unable to satified request \n";
    std::abort();
}
int main()
{
    std::set_new_handler(outofMem);
    int*pBigDataArray=new int[100000000L];
}


class X{
public:
    static void outOfMemory();
};
class Y{
public:
    static void outOfMemory();
};
int main()
{
    X* p1=new X();

    return 0;
}









