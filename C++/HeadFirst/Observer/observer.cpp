#include<iostream>
using namespace std;
//错误示范
class currentCondition
{
public:
    void update(float temp,float humidity,float pressure)
    {
        std::cout<<temp<<humidity<<pressure<<std::endl;
    }
};
class statics
{
public:

    void update(float temp,float humidity,float pressure)
    {
        std::cout<<temp<<humidity<<pressure<<std::endl;
    }
};
class forcase
{
public:
    void update(float temp,float humidity,float pressure)
    {
        std::cout<<temp<<humidity<<pressure<<std::endl;
    }
};
class WeatherData{
public:
    void measurementsChanged()
    {
        m_temp = getTemperature();
        m_humidity = gethumidity();
        m_pressure = getPressure();
    }
    void update();//整合的数据向外界展示
    //获取数据的来源
    float getTemperature();
    float gethumidity();
    float getPressure();

private:
    currentCondition  currentConditionDisplay;
    statics           staticsDisplay;
    forcase           forcaseDisplay;
    //从外界数据源
    float m_temp;
    float m_humidity;
    float m_pressure;
};
void WeatherData::update()
{
    currentConditionDisplay.update(m_temp,m_humidity,m_pressure);
    staticsDisplay.update(m_temp,m_humidity,m_pressure);
    forcaseDisplay.update(m_temp,m_humidity,m_pressure);
}