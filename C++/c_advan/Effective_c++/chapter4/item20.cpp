/*
宁以pass-by-reference-to-const 替换pass-by-value
*/
#include<iostream>
#include<string>
class Person{
public:
    Person();
    virtual ~Person();
private:
    std::string name;
    std::string address;
};
class Student:public Person{
public:
    Student();
    ~Student();
private:
    std::string schoolName;
    std::string schoolAddress;
};

class Window{
public:
    std::string name()const;
    virtual void display()const;
};

class WindowWithScrollBars:public Window{
public:
    virtual void display()const;
};
void printNameAndDisplay(Window w)//参数可能会被切割
{
    std::cout<<w.name();
    w.display();
}

int main()
{
    WindowWithScrollBars wwsb;
    printNameAndDisplay(wwsb);//wwsb的WindowWithScrollBars会隐式转换未Window类型
    //构造函数会调用基类函数


}
