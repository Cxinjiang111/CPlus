/*
例如有许多应用框架都要求derived classes内的virtual函数代码的
第一个动作就先调用base class的对应函数
*/
#include<iostream>
class Window{
public:
    Window();
    virtual void onResize(){
        std::cout<<"window"<<std::endl;
    }
};
class SpecialWindow:public Window{
public:
    SpecialWindow();
    virtual void onResize(){
        //derived onResize实现代码将*this转型为Window，然后调用onResize 
        std::cout<<"SpecialWindow before"<<std::endl;
        static_cast<Window>(*this).onResize();
        std::cout<<"window later"<<std::endl;
    }
};
/*
在代码中强调了转型动作（那是个新式转型，但若使用旧式转型也不能改变 以下事实）。
一如你所预期， 这段程序将＊this转型为Window, 对函数onResize 的调用也因此调用了Window: :onResize。
但恐怕你没想到，它调用的并不是当前对象上的函数，而是稍早转型动作所建立的一个“ *this对象之base class成分” 的 
暂时副本身上的onResize! （译注： 函数就是函数， 成员函数只有一份， “调用 起哪个对象身上的函数” 有什么关系呢？
关键在于成员函数都有个隐藏的 this指针， 会因此影响成员函数操作的数据。）再说一次，上述代码并非在当前对象身上 
调用Window::onResize之后又在该对象身上执行SpecialWindow专属动作。 不， 它是在 “ 当前对象之baseclass成分” 
的副本上调用Window: :onResize,然后在当 前对象身上执行SpecialWindow专属动作。如果Window::onResize修改了对象内容
（不能说没有可能性， 因为onResize是个non-const成员函数）， 当前对象其 实没被改动，改动的是副本。
然而SpecialWindow::onResize内如果也修改对象， 当前对象真的会被改动。 这使当前对象进入一种 “伤残” 状态：
其base class成分 的更改没有落实，而derivedclass成分的更改倒是落实了。


*/
int main()
{
    SpecialWindow s;
    s.onResize();
    //没有办法进行编译
    // undefined reference to `SpecialWindow::SpecialWindow()'
    return 0;
}