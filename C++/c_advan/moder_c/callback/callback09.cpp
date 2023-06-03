/*
Qt 信号槽实现信号的发送和接收，类似观察者。简单说明：
sender：发出信号的对象
signal：发送对象发出的信号
receiver：接收信号的对象
slot：接收对象在接收到信号之后所需要调用的函数（槽函数）
emit：发送信号
*/
#include<iostream>
#include<functional>
using namespace std;
//信号对象类
class SignalObject{
public:
    void connect(std::function<void(int)>slotFun)
    {
        m_callfun=slotFun;
    }
    void emitSignal(int signalVal)
    {
        m_callfun(signalVal);
    }
private:
    std::function<void(int)>m_callfun;
};
//槽对象类
class SlotObject{
public:
    SlotObject();
public:
    void slotMember(int signalVal)
    {
        std::cout<<"signal:"<<signalVal<<"  recv:  "<<this<<std::endl;
    }
};
SlotObject::SlotObject()
{

}
int main(){
    SignalObject signalObject;
    SlotObject slotObject;
    std::cout<<"slotObject:"<<&slotObject<<std::endl;
    signalObject.connect(bind(&SlotObject::slotMember,slotObject,std::placeholders::_1));
    signalObject.emitSignal(1);

    return 0;
}
