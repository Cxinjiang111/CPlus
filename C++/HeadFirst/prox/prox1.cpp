#include<iostream>
#include<string>
using namespace std;
//女孩是真正的糖果机
class Gril
{
private:
    string m_string;
public:
    Gril(const string& string) : m_string(string) {};
    ~Gril() {};
    string getName() const { return m_string; }
};
//为了stub和skleten一样的接口，制作一个基类
class Profession
{
public:
    Profession() {}
    virtual ~Profession() {} 
    virtual void profession();
};
void Profession::profession(){}
//为女孩端提供向外数据的接口服务代理
class YoungMan:public Profession 
{
private:
    Gril m_gril;//拿到女孩端的数据
public:
YoungMan(const Gril& gril) : m_gril(gril) {};
    void profession()
    {
        cout<<"young man love "<<m_gril.getName()<<endl;
    }
};
//客户端的代理
class ManProxy:public Profession
{
private:
    YoungMan* m_pMan;//拿到服务端的数据 这个算是注册
public:
    ManProxy(const Gril& gril)
    {
        m_pMan=new YoungMan(gril);//这个是拿到服务端的数据的接口
    }
    void profession()
    {
        m_pMan->profession();
    }
};
int main()
{
    Gril gril("young");
    Profession* pMan=new ManProxy(gril);
    pMan->profession();

    return 0;
}