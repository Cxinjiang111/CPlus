#ifndef __DERIVE_BASE_H__
#define __DERIVE_BASE_H__
#include <iostream>
using namespace std;
class BaseTest
{
private:
    virtual void display() { cout << "Base display" << endl; }
    void say() { cout << "Base say()" << endl; }

public:
    virtual void func() { cout << "Base func()" << endl; }
    void exec()
    {
        display();
        say();
    }
    void f1(string a) { cout << "Base f1(string)" << endl; }
    void f1(int a) { cout << "Base f1(int)" << endl; }

    void exec2()
    {
        display();
        say();
    }
};

class DeriveA : public BaseTest
{
public:
    void display() { cout << "DeriveA display()" << endl; }
    void f1(int a, int b) { cout << "DeriveA f1(int,int)" << endl; }
    void say() { cout << "DeriveA say()" << endl; }
    virtual void func() { cout << "DeriveA func()" << endl; }
    void use_base_f1(int a, int b)
    {
        BaseTest::f1(2);
        BaseTest::f1("test");
        cout << "DeriveA f1(int, int)" << endl;
    }
    void exec2()
    {
        display();
        say();
    }
};

extern void derive_base_test1();
#endif