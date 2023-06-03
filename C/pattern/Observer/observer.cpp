#include<iostream>
#include<vector>
using namespace std;
class Clickable;
class ClickabkeObserver;
class Clickable{ //父类为所有功能提供虚函数接口
public:
    virtual void click()=0;
    virtual void addClickableObserver(ClickabkeObserver *observer)=0;
    virtual void removeClickableObserver(ClickabkeObserver*observer)=0;
};
class ClickabkeObserver{
public:
    virtual void click(Clickable *clickable)=0;
};
class Button:public Clickable{
public:
    vector<ClickabkeObserver*>observers; //将所有的观察者放入到数组中
    string color;
    int x,y;
    void click(){
        cout<<"按钮被单机"<<endl;
        for(int i=observers.size()-1;i>=0;i--){
            observers[i]->click(this);
        }
    }
    void addClickableObserver(ClickabkeObserver *observer){
        observers.push_back(observer);
    }
    void removeClickableObserver(ClickabkeObserver *observer){
    }
};
//提供扩展接口 添加不同的观察者
class ChangeCoordinateObserver:public ClickabkeObserver{
public:
    void click(Clickable *clickable){
        Button *b=(Button*)clickable;
        b->x=100;
        b->y=90;
    }
};
class ChangeColorObserver:public ClickabkeObserver{
public:
    void click(Clickable *clickable){
        Button *b=(Button *)clickable;
        b->color="red";
    }   
};
class OtherObserver:public ClickabkeObserver{
    public:
    void click(Clickable *clickable){
        cout<<"其他操作"<<endl;
    }
};
//-----------------
int main()
{
    Button *button=new Button();
    button->color="blue";
    button->x=0;
    button->y=0;
    button->addClickableObserver(new ChangeColorObserver());
    button->addClickableObserver(new OtherObserver());
    button->addClickableObserver(new ChangeCoordinateObserver());
    button->click();
    cout<<"颜色："<<button->color<<"坐标"<<button->x<<button->y<<endl;



}