#include<iostream>
#include<functional>
using namespace std;

class Object{
public:
    Object *self(){
        return this;
    }
    std::function<Object*(void)> m_sender;
};
//槽函数， 也就是回调函数，需要执行的具体操作
class SlotObject3:public Object{
public:
    SlotObject3(){}
public:
    void slotMember(int signal){
        if(m_sender)
        {
            std::cout<<"sender:"<<m_sender()<<std::endl;
        }
        std::cout<<"signal:"<<signal<<" recv:"<<this<<std::endl;
    }
};
//负责发送信号，并去回调槽函数，相当于中间商
class SignalObject3:public Object{
public:
    //给对象赋值，完成信号与槽 也就是信号知道我可以调用具体那个函数了，但不具体执行这个操作，回调那个函数了
    void connect(SlotObject3*recver,std::function<void(SlotObject3*,int)>slot)
    {
        m_recever=recver;
        m_callFun=slot;
    }
    void emitSignal(int signal) //发送信号 绑定并执行回调函数
    {
        m_recever->m_sender=std::bind(&SlotObject3::self,this);
        m_callFun(m_recever,signal);
        m_recever->m_sender=nullptr;
    }
private:
    SlotObject3 *m_recever;//被调用者
    std::function<void(SlotObject3*,int)>m_callFun;//绑定的被调用者
};
int main()
{
    SignalObject3 signalObject3;
    SlotObject3 slotObject3;

    std::cout<<" signalObject3:  "<<&signalObject3<<std::endl;
    std::cout<<" slotObject3:  "<<&slotObject3<<std::endl;    

    std::function<void(SlotObject3*,int)>slot3=&SlotObject3::slotMember;
    signalObject3.connect(&slotObject3,slot3);//完成与槽函数的连接，相当于注册
    signalObject3.emitSignal(3);//具体执行槽函数，

    return 0;
}