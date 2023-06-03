#include<iostream>
using namespace std;
/*
代理模式：为其它对象提供一种代理以控制这个对象的访问。
在某些情况下，一个对象不适合或者不能直接引用另一个对象，
而代理对象可以在客户端和目标对象之间起到中介作用。
优点：
职责清晰。真实的角色只负责实现实际的业务逻辑，
不用关心其它非本职责的事务，通过后期的代理完成具体的任务。这样代码会简洁清晰。
代理对象可以在客户端和目标对象之间起到中介的作用，这样就保护了目标对象。
扩展性好。
*/
//****
class Girl{
public:
    Girl(const string &name="girl"):m_string(name){}
    string getName(){
        return m_string;
    }
private:
    string m_string;
};
//基类
class Profession{
public:
    virtual ~Profession(){}
    virtual void profess()=0;
};
//真实的对象 提供服务的对象
class YoungMan:public Profession{
public:
    YoungMan(const Girl&girl):m_girl(girl){}
    void profess(){
        cout<<"YoungMan:public Profession"<<m_girl.getName().data()<<endl;
    }
private:
    Girl m_girl;
};
//只提供访问的接口的对象 提供一种间接性
class ManProxy:public Profession{
public:
    ManProxy(const Girl&girl):m_pMan(new YoungMan(girl)){}
    ~ManProxy(){
        delete m_pMan;
        m_pMan=nullptr;
    }
    void profess(){
        m_pMan->profess();//在ManProxy访问YoungMan的功能函数
    }
private:
    YoungMan *m_pMan;
};
int main(){
    Girl girl("hei hei");
    ManProxy *proxy=new ManProxy(girl);
    proxy->profess();
    delete proxy;
    proxy=nullptr;
    return 0;
}