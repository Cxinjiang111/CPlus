/*
解决之道是拿掉转型动作，代之以你真正想说的话。
你并不想哄骗编译器将*this视为一个base class对象，你只是想调用base class版本的onResize函数，
令它作用千当前对象身上。 所以请这么写：
*/
#include<iostream>
class Window{
public:
    Window(int a_):a(a_){};
    virtual void onResize(){
        std::cout<<"window"<<std::endl;
    }
private:
    int a;
};
class SpecialWindow:public Window{
public:
    SpecialWindow(int a_):Window::Window(a_){};
    virtual void onResize(){
        //Window::onResize();//调用Window：：onResize作用于*this身上
            static_cast<Window>(*this).onResize();
        std::cout<<"window later"<<std::endl;
    }
    
};
int main()
{
    SpecialWindow s(2);
    //s.onResize();

    Window *p=&s;
    p->onResize();
/*output
window
window later
*/
    return 0;
}