#include<iostream>
#include<string>
using namespace std;
//让所有的命令对象实现包含一个方法的接口
class Command
{
public:
    Command();
    ~Command();
    virtual void execute() = 0;//平台提供
};
Command::Command(){}
Command::~Command(){}
//根据厂商所提供的类，Light有两个方法，on off 
class Light{
public:
     bool on();
     bool off();
};
bool Light::on()
{
    return true;
}
bool Light::off()
{
    return true;
}
class LightOnCommand : public Command
{
private:
    Light *m_light;
public:
    LightOnCommand(Light  *light) : m_light(light){}
    void execute(){m_light->on();
    std::cout<<"execute  on"<<std::endl;
    }
};
//遥控器，它只有一个按钮和对应的卡槽，
class SimpleRemoteControl
{
public:
    Command *m_slot;//这里必须为指针
    SimpleRemoteControl(){}
    void setCommand(Command *command){m_slot = command;}
    void buttonWaPressed(){
        m_slot->execute();
    }
};
int main()
{
    SimpleRemoteControl *remoteControl = new SimpleRemoteControl();
    Light *plight = new Light();
    Command*pcommand = new LightOnCommand(plight);

    remoteControl->setCommand(pcommand);
    remoteControl->buttonWaPressed();
    return 0;
}



