#include<iostream>
#include<exception>
#include <cstdlib>
#include<new>
class Widget{
public:
    //用户选择的异常处理函数
    static std::new_handler set_new_handler(std::new_handler p)throw();
    static void* operator new(std::size_t size) throw(std::bad_alloc);    
private:
    static std::new_handler currentHandler;
    //static 成员必须在class定义式之外被定义
};
std::new_handler Widget::currentHandler=0;//static 成员被定义
std::new_handler Widget::set_new_handler(std::new_handler p)throw()
{
    std::new_handler oldHandler=currentHandler;
    currentHandler=p;
    return oldHandler;
}
/*


*/
class NewHandlerHolder{
public:
    explicit NewHandlerHolder(std::new_handler nh):handler(nh){}//取得目前的new-handler

private:
    std::new_handler handler;//异常处理的函数指针
    NewHandlerHolder(const NewHandlerHolder&);//构造函数 阻止copying
    NewHandlerHolder&operator=(const NewHandlerHolder&);//赋值构造函数
};
void* Widget::operator new(std::size_t size) throw()
{
    NewHandlerHolder h(std::new_handler(currentHandler));
    return ::operator new(size);//利用的时全局的operator new 
    //就是::operator new(size) 分配失败了，异常处理，栈回退的一个过程，回到上一句new_handler的过程、
}

void outOfMem();//此函数Widget对象分配失败时被调用
std::new_handler p=outOfMem;
//设定OutofMem为Widget的new-handling函数
std::new_handler Widget::set_new_handler(std::new_handler p)throw()
{
}
//如果内存分配失败，调用outofMem
Widget *pw1=new Widget;
//如果内存分配失效，调用global new-handling函数
std::string*ps=new std::string;
//设定Widget专属的new-handing函数为null
Widget::set_new_handler(nullptr);
//如果内存分配失败，立刻抛出异常，
Widget *pw2=new Widget;//

int main()
{
    Widget *p2=new (std::nothrow)Widget;//(std::nothrow)这个就是分配失败就返回0


}
