#include "../inc/vitrual_table.h"
extern void useTable(VirtualTableA *pa);
void destructVirtualTable()
{
    VirtualTableA *pa = new VirtualTableB();
    useTable(pa);
    delete pa;
}

void VirtualTableB::print()
{
    cout << "this is virtual table B" << endl;
}

void useTable(VirtualTableA *pa)
{
    //实现动态调用
    pa->print();
}

/**
1   类的静态函数和构造函数不可以定义为虚函数:
静态函数的目的是通过类名+函数名访问类的static变量，或者通过对象调用staic函数实现对static成员变量的读写，
要求内存中只有一份数据。而虚函数在子类中重写，并且通过多态机制实现动态调用，在内存中需要保存不同的重写版本。

2   构造函数的作用是构造对象，而虚函数的调用是在对象已经构造完成，并且通过调用时动态绑定。
动态绑定是因为每个类对象内部都有一个指针，指向虚函数表的首地址。而且虚函数，类的成员函数，
static成员函数都不是存储在类对象中，而是在内存中只保留一份。
 * */

class Baseclass
{

public:
    Baseclass() : a(1024) {}
    virtual void f() { cout << "Base::f" << endl; }
    virtual void g() { cout << "Base::g" << endl; }
    virtual void h() { cout << "Base::h" << endl; }
    int a;
};

// 0 1 2 3(虚函数表空间)   4 5 6 7(用来对齐)    8 9 10 11 12 13 14 15(存储的是a)

class DeriveClass : public Baseclass
{
public:
    virtual void f() { cout << "Derive::f" << endl; }
    virtual void g2() { cout << "Derive::g2" << endl; }
    virtual void h3() { cout << "Derive::h3" << endl; }
};

typedef void (*Func)();
void useVitualTable()
{
    Baseclass b;
    b.a = 1024;
    cout << "sizeof b is " << sizeof(b) << endl;

    int *p = (int *)(&b);
    cout << "pointer address of vitural table " << p << endl;
    cout << "address of a is " << p + 2 << endl;
    cout << "value of a is " << *(p + 2) << endl;
    cout << "address of vitural table" << (int *)(*p) << endl;

    Func pFun = (Func)(*(int *)(*p));
    pFun();

    pFun = (Func) * ((int *)(*p) + 2);
    pFun();

    pFun = (Func)(*((int *)(*p) + 4));
    pFun();
}

void deriveTable()
{
    DeriveClass d;
    int *p = (int *)(&d);
    int *virtual_tableb = (int *)(*p);
    Func pFun = (Func)(*(virtual_tableb));
    pFun();

    pFun = (Func)(*(virtual_tableb + 2));
    pFun();

    pFun = (Func)(*(virtual_tableb + 4));
    pFun();
    pFun = (Func)(*(virtual_tableb + 6));
    pFun();
    pFun = (Func)(*(virtual_tableb + 8));
    pFun();
}

extern void aligneTest()
{
    AligneTest::A a;
    AligneTest::B b;
    AligneTest::C c;
    AligneTest::D d;
    AligneTest::E e;
    cout << "sizeof(a): " << sizeof(a) << endl;
    cout << "sizeof(b): " << sizeof(b) << endl;
    cout << "sizeof(c): " << sizeof(c) << endl;
    cout << "sizeof(d): " << sizeof(d) << endl;
    cout << "sizeof(e): " << sizeof(e) << endl;
}