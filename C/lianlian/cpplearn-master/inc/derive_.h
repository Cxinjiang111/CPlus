#ifndef __DERIVE__H__
#define __DERIVE__H__
#include <iostream>
using namespace std;

//基类
class Base
{
public:
    Base() : m_nbase(0), m_nbase2(m_nbase + 100) {}
    Base(int n) : m_nbase(n), m_nbase2(m_nbase + 100)
    {
        cout << "this is Base construct " << endl;
    }
    virtual ~Base()
    {
        cout << "this is Base destruct " << endl;
    }

    virtual void printData()
    {
        cout << "this is Base printData " << endl;
        cout << "data is " << m_nbase << endl;
        // cout << "base2 data is " << m_nbase2 << endl;
    }

    void printData2()
    {
        cout << "base2 data is " << m_nbase2 << endl;
    }

    int SizeOf(char p[])
    {
        return sizeof(p);
    }

    int SizeOf2(char *p)
    {
        return sizeof(p);
    }

private:
    int m_nbase;
    int m_nbase2;
};

//子类

class Derive : public Base
{
public:
    Derive(int n) : Base(n), m_nderive(n)
    {
        cout << "this is Derive construct " << endl;
    }

    virtual ~Derive()
    {
        cout << "this is Derive destruct " << endl;
    }

    void printData()
    {
        cout << "this is Derive printData" << endl;
    }

private:
    int m_nderive;
};

extern void
derive_test();

extern int binary_search(int nums[], int begin, int end, int target);

#endif