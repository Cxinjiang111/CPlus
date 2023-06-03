#include<iostream>
using namespace std;
/*
当一个对象内在状态改变时允许改变行为，
这个对象看起来像改变了其类型。状态模式的核心是封装，
状态的变更引起行为的变动，从外部看来就好像该对象对应的类发生改变一样
21.2 优点
　　■ 结构清晰。
　　■ 遵循设计原则。
　　■ 封装性非常好。
21.3 缺点
　　■ 子类太多，不易管理。
21.4 使用场景
　　■ 对象的行为依赖于它所处的状态，即行为随状态改变而改变的场景。
　　■ 对象在某个方法里依赖于一重或多重条件分支语句，
此时可以使用状态模式将分支语句中的每一个分支都包装到一个单独的类中，
使得这些条件分支语句能够以类的方式独立存在和演化。
如此，维护这些独立的类就不再影响到系统的其他部分
*/
class Channel{
public:
    virtual void display()=0;
};
class CCTV1:public Channel{
public:
    void display(){
        cout<<"CCTV1"<<endl;
    }
};
class CCTV2:public Channel{
public:
    void display(){
        cout<<"CCTV2"<<endl;
    }
};
class TV{
public:
    static Channel*cctv1;
    static Channel*cctv2;
private:
    Channel*channel;
public:
    void setChannel(Channel*channel){
        this->channel=channel;
    }
    void disCCTV1(){
        this->setChannel(cctv1);
        this->channel->display();
    }
    void disCCTV2(){
        this->setChannel(cctv2);
        this->channel->display();
    }
};
//这是？？？？
Channel*TV::cctv1=new CCTV1();
Channel*TV::cctv2=new CCTV2();
int main(){
    TV tv;
    tv.disCCTV1();
    tv.disCCTV2();
    return 0;
}


