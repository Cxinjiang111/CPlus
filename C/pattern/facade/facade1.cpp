#include<iostream>
using namespace std;
/*
外观模式：为子系统中的一组接口定义一个一致的界面；外观模式提供一个高层的接口，
这个接口使得这一子系统更加容易被使用；对于复杂的系统，
系统为客户端提供一个简单的接口，把负责的实现过程封装起来，
客户端不需要连接系统内部的细节。
以下情形建议考虑外观模式：
设计初期阶段，应有意识的将不同层分离，层与层之间建立外观模式。
开发阶段，子系统越来越复杂，使用外观模式提供一个简单的调用接口。
一个系统可能已经非常难易维护和扩展，但又包含了非常重要的功能，
可以为其开发一个外观类，使得新系统可以方便的与其交互。
优点：
实现了子系统与客户端之间的松耦合关系。
客户端屏蔽了子系统组件，减少了客户端所需要处理的对象数据，
使得子系统使用起来更方便容易。
更好的划分了设计层次，对于后期维护更加的容易。
*/
class Control{
public:
    virtual void start()=0;
    virtual void shutdown()=0;
};
//
class Host:Control{
public:
    void start(){
        cout<<"Host start"<<endl;
    }
    void shutdown(){
        cout<<"Host shutdown"<<endl;
    }
};
//
class LCDDisplay:public Control{
public:
    void start(){
        cout << "LCD Display start" << endl;
    }
    void shutdown(){
        cout << "LCD Display shutdonw" << endl;
    }
};
class Computer{
public:
    void start(){
        m_host.start();
        m_display.start();
        cout<<"computer start<"<<endl;
    }  
    void shutdown(){
        m_host.shutdown();
        m_display.shutdown();
    }

private:
    Host m_host;
    LCDDisplay m_display;
};
int main(){
    Computer computer;
    computer.start();
    computer.shutdown();
    return 0;
}