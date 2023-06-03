#include "../inc/derive_base.h"
#include <memory>
void derive_base_test1()
{
    DeriveA a;
    BaseTest *b = &a;
    shared_ptr<BaseTest> c = make_shared<BaseTest>();
    //输出DeriveA func()
    b->func();
    //输出DeriveA func()
    a.func();
    //输出Base f1(string)
    b->f1("abc");
    //输出Base f1(int)
    b->f1(3);
    //输出DeriveA f1(int,int)
    a.f1(3, 5);

    a.use_base_f1(2, 4);
    cout << "========================" << endl;
    //输出DeriveA display()
    //输出Base say()
    b->exec();
    //输出DeriveA display()
    //输出Base say()
    a.exec();
    //输出Base display
    //输出Base say()
    c->exec();
    cout << "======================== \n"
         << endl;
    //输出 DeriveA display()
    //输出 Base say()
    b->exec2();
    //输出 DeriveA display()
    //输出 DeriveA say()
    a.exec2();
    //输出 Base display
    //输出 Base say()
    c->exec2();
}

/*
考察一个函数是被子类还是基类调用时应该分以下几种情况
1  该函数是虚函数并且被子类重写，如果是基类指针指向子类对象，调用该函数则引发多态机制，调用子类的虚函数
2  如果该函数时虚函数并且没有被重写，那么无论调用的对象是基类指针还是子类对象，还是基类对象，
还是子类指针都是调用基类的这个虚函数
3  如果该函数不是虚函数，如果该函数被子类覆盖(子类重新定义了同名函数)，那么调用规则就是子类调用子类的该函数，
基类调用该基类的函数。
4  如果该函数不是虚函数，并且子类没有定义同名函数(没有覆盖基类同名函数)，那么无论是子类还是基类的指针或者对象，
统一调用的是基类的函数。
5  如果第4点里基类的函数(没有被子类覆盖)，但是内部调用了基类的虚函数，并且该虚函数被子类重写，这时内部这个虚函数调用规则
就要看调用对象的实际类型，符合1的调用标准，多态就走子类，不是多态就走基类(此时符合2标准)
6  如果第3点里基类的函数(被子类覆盖)，但是内部调用了基类的虚函数，并且该虚函数被子类重写，这时内部这个虚函数调用规则
就要看调用对象的实际类型，符合1的调用标准，多态就走子类，不是多态就走基类(此时符合2标准)
*/