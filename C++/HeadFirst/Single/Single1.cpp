#include<iostream>
using namespace std;
#define ONEMETHOD 1
class ChocolateBolier
{
private:
    bool m_empty;
    bool m_boiled;
#ifdef ONEMETHOD
    static ChocolateBolier *unique;
public:
    static ChocolateBolier*GetInstance()
    {
        if(unique==nullptr) 
            unique = new ChocolateBolier();
        return unique;
    }
#elif defined ONEMETHOD
//在静态初始化器中创建单件，这段代码保证了线程安全  在任何线程访问这个
//静态变量之前，一定先创建此实例
    static ChocolateBolier *unique=new ChocolateBolier();
public:
    static ChocolateBolier*GetInstance()
    {//已经有实例了，直接使用它
        return unique;
    }
#endif 
    ChocolateBolier()
    {
        m_empty=true;
        m_boiled=false;
    }
    void fill() //在锅炉内加入原料，锅炉必须是空的，一旦填入原料，empty和boiled标志设置好
    {
        if(isEmpty())
        {
            m_empty=false;
            m_boiled=false;
        }
    }
    void drain()
    {
        if(!isEmpty()&&isBoiled())
        {//排出煮沸的巧克力和牛奶
            m_empty=true;
        }
    }
    void boil()
    {
        if(!isEmpty()&&!isBoiled())
        {//将炉内物煮沸
            m_boiled=true;
        }
    }
    bool isEmpty()
    {
        return m_empty;
    }
    bool isBoiled()
    {
        return m_boiled;
    }
};

