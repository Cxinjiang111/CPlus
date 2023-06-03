#include<iostream>
using namespace std;
/*
适配器模式可以将一个类的接口转换成客户端希望的另一个接口，
使得原来由于接口不兼容而不能在一起工作的那些类可以在一起工作。
通俗的讲就是当我们已经有了一些类，而这些类不能满足新的需求，
此时就可以考虑是否能将现有的类适配成可以满足新需求的类。
适配器类需要继承或依赖已有的类，实现想要的目标接口。

缺点：过多地使用适配器，会让系统非常零乱，不易整体进行把握。
比如，明明看到调用的是 A 接口，其实内部被适配成了 B 接口的实现，
一个系统如果太多出现这种情况，无异于一场灾难。因此如果不是很有必要，
可以不使用适配器，而是直接对系统进行重构。
*/
/*
* 关键代码：适配器继承或依赖已有的对象，实现想要的目标接口。
* 以下示例中，假设我们之前有了一个双端队列，新的需求要求使用栈和队列来完成。
  双端队列可以在头尾删减或增加元素。而栈是一种先进后出的数据结构，添加数据时添加到栈的顶部，删除数据时先删   除栈顶部的数据。因此我们完全可以将一个现有的双端队列适配成一个栈。
*/
//
class Deque{
public:
    void push_back(int x){
        cout<<"deque push_back"<<x<<endl;
    }
    void push_front(int x){
        cout<<"deque push_font"<<x<<endl;
    }
    void pop_back(){
        cout<<"deque pop_back"<<endl;
    }
    void pop_front(){
        cout<<"deque pop_back"<<endl;
    }

};
class Sequence{
public:
    virtual void push(int x)=0;
    virtual void pop()=0;
};
class Stack:public Sequence{
public: 
    void push(int x){
        m_deque.push_back(x);
        cout<<"stack pop_back"<<endl;
    }
    void pop(){
        m_deque.pop_back();      
        cout<<"stack pop_back"<<endl;
    }
private:
    Deque m_deque;
};
class Queue:public Sequence{
public: 
    void push(int x){
        m_deque.push_front(x);
        cout<<"queue pop_back"<<endl;
    }
    void pop(){
        m_deque.pop_front();
        cout<<"queue pop_back"<<endl;
    }
private:
    Deque m_deque;
};