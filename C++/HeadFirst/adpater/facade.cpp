#include<iostream>
using namespace std;
class Amplifier
{
public:
    void on(){std::cout<<" on"<<std::endl;}
    void off(){std::cout<<" off "<<std::endl;}
    
};
class Tuner
{
public:
    void on(){std::cout<<" on"<<std::endl;}
    void off(){std::cout<<" off "<<std::endl;}
    
};
class DvdPlayer
{
public:
    void on(){std::cout<<" on"<<std::endl;}
    void off(){std::cout<<" off "<<std::endl;}
    
};
class Projector
{
public:
    void on(){std::cout<<" on"<<std::endl;}
    void off(){std::cout<<" off "<<std::endl;}
    
};
class TheaterLights
{
public:
    void on(){std::cout<<" on"<<std::endl;}
    void off(){std::cout<<" off "<<std::endl;}
    
};
class Screen
{
public:
    void on(){std::cout<<" on"<<std::endl;}
    void off(){std::cout<<" off "<<std::endl;}
    
};
class PopcornPopper
{
public:
    void on(){std::cout<<" on"<<std::endl;}
    void off(){std::cout<<" off "<<std::endl;}
    
};
class HomeThreateFacade
{
private:
    Amplifier* m_amp;
    Tuner *m_tuner;
    DvdPlayer *m_dvdPlayer;
    Projector *m_projector;
    TheaterLights *m_theaterLights;
    Screen *m_screen;
    PopcornPopper *m_popcornPopper;
    //外观模式将子系统中的每一个组件的引用都传入到他的构造器中
    //然后外观把他们赋值给相应的实例变量
    HomeThreateFacade(Amplifier* amp,
                    Tuner *tuner,
                    DvdPlayer *dvdPlayer,
                    Projector *projector,
                    TheaterLights *theaterLights,
                    Screen *screen,
                    PopcornPopper *popcornPopper)
    {
        m_amp=amp;
        m_tuner=tuner;
        m_dvdPlayer=dvdPlayer;
        m_projector=projector;
        m_theaterLights=theaterLights;
        m_screen=screen;
        m_popcornPopper=popcornPopper;
    }
    void watchMovie(string move)
    {
        m_popcornPopper->on(); //具体的内部实现有组件自身去实现
        m_amp->on();
        m_tuner->on();
        m_dvdPlayer->on();
        m_projector->on();
        m_theaterLights->on();
        m_screen->on();
        m_popcornPopper->on();
    }
    void endwatchMovie(string move)
    {
        m_popcornPopper->on(); //具体的内部实现有组件自身去实现
        m_amp->off();
        m_tuner->off();
        m_dvdPlayer->off();
        m_projector->off();
        m_theaterLights->off();
        m_screen->off();
        m_popcornPopper->off();
    }
};
