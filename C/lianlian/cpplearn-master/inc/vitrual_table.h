#ifndef VIRTUAL_TABLE_H__
#define VIRTUAL_TALBE_H__
#include <iostream>
using namespace std;
class VirtualTableA
{
public:
    virtual ~VirtualTableA()
    {
        cout << "Desturct Virtual Table A" << endl;
    }

    virtual void print()
    {
        cout << "print virtual table A" << endl;
    }
};

class VirtualTableB : public VirtualTableA
{
public:
    virtual ~VirtualTableB()
    {
        cout << "Desturct Virtual Table B" << endl;
    }

    virtual void print();
};
#endif

extern void destructVirtualTable();
extern void useVitualTable();
extern void deriveTable();

namespace AligneTest
{
    class A
    {
    };

    class B
    {
        char ch;
        void func()
        {
        }
    };

    class C
    {
        char ch1; //占用1字节
        char ch2; //占用1字节
        virtual void func()
        {
        }
    };

    class D
    {
        int in;
        virtual void func()
        {
        }
    };

    class E
    {
        char m;
        virtual void func()
        {
        }
    };
}

extern void aligneTest();