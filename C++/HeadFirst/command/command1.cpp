#include<iostream>
#include<string>
using namespace std;
//让所有的命令对象实现包含一个方法的接口
class Command
{
public:
    Command();
    ~Command();
    virtual void execute();//平台提供
    virtual void undo();//平台提供
};
Command::Command(){}
Command::~Command(){}
void Command::execute(){}
class OnCommand:public Command
{
public:
    OnCommand();
    ~OnCommand();
    virtual void execute();//平台提供
};
OnCommand::OnCommand(){}
OnCommand::~OnCommand(){}
void OnCommand::execute(){}
class NoCommand:public Command
{
public:
    NoCommand();
    ~NoCommand();
    virtual void execute();//平台提供
};
NoCommand::NoCommand(){}
NoCommand::~NoCommand(){}
void NoCommand::execute(){}
//根据厂商所提供的类，Light有两个方法，on off 

//遥控器，它只有一个按钮和对应的卡槽，
class RemoteControl
{
public:
    //这里有7个卡槽
    Command *m_onCommands[7];
    Command *m_offCommands[7];
    RemoteControl()
    {
        Command *noCommand = new OnCommand();
        Command *onCommands = new OnCommand();
        for(int i = 0; i < 7;i++)
        {
            m_onCommands[i] = onCommands;
            m_offCommands[i] = noCommand;
        }
    }
    void SetCommand(int slot,Command *onCommand,Command *offCommand)
    {
        m_onCommands[slot] = onCommand;
        m_offCommands[slot] = offCommand;
    }
    void onButtonWasPushed(int slot)
    {
        if(m_onCommands[slot]==nullptr) return;
        m_onCommands[slot]->execute();
    }
    void offButtonWasPushed(int slot)
    {
        if(m_offCommands[slot]==nullptr) return;
        m_offCommands[slot]->execute();
    }
    string toString()
    {
        std:cout<<"remoteControl"<<std::endl;
        for(int i = 0; i < 7; i++)
        {

        }
    }
};
//撤销的操作
class RemoteControlWithUndo
{
public:
    //这里有7个卡槽
    Command *m_onCommands[7];
    Command *m_offCommands[7];
    Command *m_undoCommand;
    RemoteControlWithUndo()
    {
        Command *noCommand = new OnCommand();
        Command *onCommands = new OnCommand();
        for(int i = 0; i < 7;i++)
        {
            m_onCommands[i] = onCommands;
            m_offCommands[i] = noCommand;
        }
        m_undoCommand=noCommand;
    }
    void SetCommand(int slot,Command *onCommand,Command *offCommand)
    {
        m_onCommands[slot] = onCommand;
        m_offCommands[slot] = offCommand;

    }
    void onButtonWasPushed(int slot)
    {
        if(m_onCommands[slot]==nullptr) return;
        m_onCommands[slot]->execute();
        m_undoCommand=m_onCommands[slot];
    }
    void offButtonWasPushed(int slot)
    {
        if(m_offCommands[slot]==nullptr) return;
        m_offCommands[slot]->execute();
        m_undoCommand=m_offCommands[slot];
    }
    string toString()
    {
        std:cout<<"remoteControl"<<std::endl;
        for(int i = 0; i < 7; i++)
        {

        }
    }
    void undoButtonWasPushed()
    {
        m_undoCommand->undo();
    }
};
class CeilingFan
{
public:
//之所以这么static 因为只有一个按钮，那么全局就只有唯一一个状态
    static int HIGH;
    static int MEDIUM;
    static int LOW;
    static int OFF;
private:
    string m_location;
    int m_speed;
public:
    CeilingFan(string location):m_location(location),m_speed(LOW){}
    void high(){m_speed=HIGH;}
    void medium(){m_speed=MEDIUM;}
    void low(){m_speed=LOW;}
    void off(){m_speed=OFF;}
    int getSpeed(){return m_speed;}
};
class CeilingFanHighCommand:public Command{
private:
    CeilingFan *m_ceilingFan;
    int m_prevSpeed;
public:
    CeilingFanHighCommand(CeilingFan *ceilingFan){m_ceilingFan=ceilingFan;};
    void execute()
    {
        m_prevSpeed=m_ceilingFan->getSpeed();
        m_ceilingFan->high();
    }
    void undo(){
        if(m_prevSpeed==CeilingFan::HIGH)
        {
            m_ceilingFan->high();
        }
        else if(m_prevSpeed==CeilingFan::MEDIUM)
        {
            m_ceilingFan->medium();
        }
        else if(m_prevSpeed==CeilingFan::LOW)
        {
            m_ceilingFan->low();
        }
        else if(m_prevSpeed==CeilingFan::OFF)
        {
            m_ceilingFan->off();
        }
    }

};


//灯  实现命令
//第一个开
class Light{
public:
    Light(string name);
    Light();
    ~Light();
     bool on();
     bool off();
private:
    string m_name;
};
Light::Light(string name)
{
    m_name = name;
}
Light::Light(){}
Light::~Light(){}
bool Light::on()
{
    std::cout<<m_name<<"Light on"<<std::endl;
    return true;
}
bool Light::off()
{
    std::cout<<m_name<<"Light off"<<std::endl;
    return true;
}
class LightOnCommand : public OnCommand
{
private:
    Light *m_light;
public:
    LightOnCommand(Light  *light) : m_light(light){}
    void execute(){m_light->on();
    std::cout<<"execute  on"<<std::endl;
    }
};
//第一个关
class LightOffCommand : public NoCommand {
private:
    Light *m_light;
public:
    LightOffCommand(Light  *light) : m_light(light){}
    void execute()
    {
        m_light->off();
        std::cout<<"execute  off"<<std::endl;
    }
};
//第二排留给音响的命令的实现
class Stereo
{
public:
    Stereo();
    ~Stereo();
    Stereo(string name);
    void on(){std::cout<<"Stereo on"<<std::endl;}
    void off(){std::cout<<"Stereo off"<<std::endl;}
    void setCd(){std::cout<<"Stereo setCd"<<std::endl;}
    void setDvd(){std::cout<<"Stereo setDvd"<<std::endl;}
    void setVolume(){std::cout<<"Stereo setVolume"<<std::endl;}
private:
    string m_steroname;
};
Stereo::Stereo(){}
Stereo::Stereo(string name){m_steroname=name;}
Stereo::~Stereo(){}
//第二排控制音响开
class StereOnWithCDCommand :public Command
{
private:
    Stereo *m_stereo;
public:
    StereOnWithCDCommand(Stereo *stereo)
    {m_stereo=stereo;}
    void execute() //command基类只需要提供这个流程性的函数即可
    {
        m_stereo->on();
        m_stereo->setCd();
        m_stereo->off();
        m_stereo->setVolume();
        m_stereo->setDvd();
    }
};
class StereOffWithCDCommand :public Command
{
private:
    Stereo *m_stereo;
public:
    StereOffWithCDCommand(Stereo *stereo)
    {m_stereo=stereo;}
    void execute() //command基类只需要提供这个流程性的函数即可
    {
        m_stereo->on();
        m_stereo->setCd();
        m_stereo->off();
        m_stereo->setVolume();
        m_stereo->setDvd();
    }
};
int main()
{
    RemoteControl *premoteControl= new RemoteControl();
    //为卡槽创建合适的装置
    Light *plight= new Light("Living name ");
    Light *pkitchentLight= new Light("kitchen");
    Stereo *pstereo= new Stereo("stereo");

    //创建所有的电灯命令对象
    LightOnCommand *plightonCommand=new LightOnCommand(plight);
    LightOffCommand *plightoffCommand=new LightOffCommand(plight);
    LightOnCommand *pkitchenonlight=new LightOnCommand(pkitchentLight);
    LightOffCommand *pkitchenofflight=new LightOffCommand(pkitchentLight);
    //为stereo创建命令对象
    StereOnWithCDCommand *pstereoOnWithCDCommand=new StereOnWithCDCommand(pstereo);
    StereOffWithCDCommand *pstereoOffWithCDCommand=new StereOffWithCDCommand(pstereo);

    //给上述指定好的自定义装置指定到remoteControl相应的卡槽
    premoteControl->SetCommand(0,plightonCommand,plightoffCommand);
    premoteControl->SetCommand(1,pkitchenonlight,pkitchenofflight);
    premoteControl->SetCommand(2,pstereoOnWithCDCommand,pstereoOffWithCDCommand);


    // premoteControl->onButtonWasPushed(0);
    // premoteControl->onButtonWasPushed(1);
    // premoteControl->onButtonWasPushed(2); 


    premoteControl->offButtonWasPushed(0);
    premoteControl->offButtonWasPushed(1);
    premoteControl->offButtonWasPushed(2); 
    CeilingFan::HIGH=3;
    CeilingFan::MEDIUM=2;
    CeilingFan::LOW=1;
    CeilingFan::OFF=0;                  
    return 0;
}