/*编写new和delete时需固守常规

*/
void *operator new(std::size_t size)throw(std::bad_alloc)
{
    using namespace std;
    if(size==0)//分配失败
    {
        size=1;
    }
    else{
        return //分配成功
    }
    while (true)
    {
        //尝试不断地分配
        //跳出循环地唯一办法是：内存被成功分配或new-handling函数做一件事就是让更多内存可用，
        //安装另一个new-handler，卸除new-handler，抛出bad_alloc异常，或是承认失败而直接return

        /* code */
    }
    if(分配成功)
    return;
    //处理异常
    new_handler globalHandler=set_new_handler(0);//
    set_new_handler(gloabalHandler);//获取这个函数指针
    if(globalHandler)
    (*globalHandler)();
    else
    throw
    std::bad_alloc();
    
}



