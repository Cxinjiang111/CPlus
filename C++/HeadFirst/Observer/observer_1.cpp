#include<iostream> 
#include<vector>
using namespace std;
class Observer{
public:
    Observer();
    ~Observer();
    virtual void update(float temp,float humidity,float pressure);
};
Observer::Observer(){}
Observer::~Observer(){}
void Observer::update(float temp,float humidity,float pressure){
    std::cout<<"Observer::update"<<std::endl;
}
// class DisplayElement{
// public:
//     DisplayElement();
//     ~DisplayElement();
//     virtual void display();
// };
// void DisplayElement::display()
// {
// }
// DisplayElement::DisplayElement(){};
// DisplayElement::~DisplayElement(){}
//Subject 需要被组合，所以不能有纯虚函数
class Subject{
public:
    Subject(){};
    virtual ~Subject(){};
    virtual void registerObserver(Observer* o);
    virtual void removeObserver(Observer& o);
    virtual void notifyObserver();
};
void Subject::registerObserver(Observer* o)
{

}
void Subject::removeObserver(Observer& o)
{

}
void Subject::notifyObserver()
{

}
class WeatherDate :public Subject{
public:
    WeatherDate(float temp,float humidity,float pressure):m_temperature(temp),m_humidity(humidity),m_pressure(pressure){};
    WeatherDate(){};
    ~WeatherDate(){};
    void registerObserver(Observer* o)override;
    void removeObserver(Observer& o) override;
    void notifyObserver() override;
    void measurementsChanged();
    void setMeasurementsChanged(float temp,float humidity,float pressure);
private: 
    vector<Observer> m_observers;
    float            m_temperature;
    float            m_humidity;
    float            m_pressure;
};
void WeatherDate::measurementsChanged()
{
    notifyObserver();
}
void WeatherDate::setMeasurementsChanged(float temp,float humidity,float pressure)
{
    m_temperature=temp;
    m_humidity=humidity;
    m_pressure=pressure;
}
void WeatherDate::registerObserver(Observer* o)
{
    m_observers.push_back(*o);
}
void WeatherDate::removeObserver(Observer& o) 
{
    for(int i=0;i<m_observers.size();++i)
    {
        if(&(m_observers[i])==&o)//这样不对 判断对象是否相等
            m_observers.erase(m_observers.begin()+i);
    }
    return ;
}
void WeatherDate::notifyObserver() 
{
    std::cout<<"WeatherDate::notifyObserver :"<<m_observers.size()<<std::endl;
    for(int i=0;i<m_observers.size();++i)
    {
        m_observers[i].update(m_temperature,m_humidity,m_pressure);
    }
}
//以上全部属于主题这边的问题，不涉及具体的观察者
class CurrentConditionsDisplay :public Observer{//,public DisplayElement
public:
    CurrentConditionsDisplay(Observer o);
    void add(Observer o);
    CurrentConditionsDisplay(){};
    void display();
    void update(float temp,float humidity,float pressure)override;    
private:
    float m_temperature;
    float m_humidity;
};
void CurrentConditionsDisplay::add(Observer o)
{

}
void CurrentConditionsDisplay::update(float temp,float humidity,float pressure)
{
    std::cout<<"CurrentConditionsDisplay::update"<<std::endl;
    m_temperature = temp;
    m_humidity = humidity;
    //display();
}
void CurrentConditionsDisplay::display()
{
    std::cout<<" m_temperature : "<<m_temperature<<" m_humidity :"<<m_humidity<<std::endl;
}
int main()
{
    WeatherDate *pweatherDate =new WeatherDate(10,10,10);
    CurrentConditionsDisplay *pcurrentconditiondisplay= new CurrentConditionsDisplay();
    pweatherDate->registerObserver(pcurrentconditiondisplay);
    pweatherDate->notifyObserver();

    return 0;
}




