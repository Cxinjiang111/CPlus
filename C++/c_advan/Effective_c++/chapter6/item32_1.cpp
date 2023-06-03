/*
另有一种思想派别处理我所谓 “所有的鸟都会飞，企鹅是鸟，但是企鹅不会飞，
喔欧＂的问题，就是为企鹅重新定义fly函数，令它产生一个运行期错误：
*/
#include<iostream>
#include<error.h>
#include<string>

class Bird{
public:
    Bird();
    virtual void fly();//fly()没有此函数的申明
};
Bird::Bird()
{

}
void error(const std::string&msg)
{
    std::cout<<msg<<std::endl;
}
class Penguin:public Bird{
public:
    Penguin();
    virtual void fly()override ;
};
Penguin::Penguin()
{

}
void Penguin::fly(){error("make fly error");}
int main()
{

    Penguin p;

    return 0;
}


