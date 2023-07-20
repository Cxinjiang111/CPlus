#include<iostream>
#include<mutex>
mutex mut;
using namespace std;
class Myclass
{
public:
    //只有一个实例会被产生
    static Myclass *getInstance(){
        return new Myclass();
    }
};
//经典的单例模式的实现，
class Singleton
{
private:
    static Singleton *uniqueInstance;//利用一个静态变量来记录Singleton类的唯一实例
    //把构造器声明为私有，只有自Singleton类内才可以调用构造器
private:Singleton(){} 
public:
//用getInstance（）方法实例化对象，并返回这个实例
    static Singleton *getInstance()
    {
        //uniqueInstance这是个静态变量，
        if(uniqueInstance == nullptr)
        {
            uniqueInstance = new Singleton();
        }
        return uniqueInstance;//Singleton是一个正常的类，具有一些其他用途的实例变量和方法
        //返回到这里就说明已经拥有一个实例了
    }
};