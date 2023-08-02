#include<iostream>
using namespace std;

class App
{
public:
    virtual ~App() {cout<<"~App"<<endl;}
    virtual void run();
};
class GameApp:public App
{
public:
    void run()
    {
        cout<<"GameApp running"<<endl;
    }
};
class TranslateApp:public App
{
public:
    void apprun()
    {
        cout<<"TranslateApp running"<<endl;
    }
};
class MobilesPhone
{
public:
    virtual ~MobilesPhone() {cout<<"MobilesPhone"<<endl;}
    virtual void apprun(App*app);
};
class Xiaomi:public MobilesPhone
{
public:
    void apprun(App*app)
    {
        app->run();
    }
};
class Huawei:public MobilesPhone
{
public:
    void apprun(App*app)
    {
        app->run();
    }
};
int main()
{
    App* gameApp = new GameApp;
    App* translateApp = new TranslateApp;
    MobilesPhone* mi = new Xiaomi;
    MobilesPhone* hua = new Huawei;
    mi->apprun(gameApp);
    mi->apprun(translateApp);
    hua->apprun(gameApp);
    hua->apprun(translateApp);
    delete hua;
    hua = nullptr;
    delete mi;
    mi = nullptr;
    delete gameApp;
    gameApp = nullptr;
    delete translateApp;
    translateApp = nullptr;
    return 0;
}

