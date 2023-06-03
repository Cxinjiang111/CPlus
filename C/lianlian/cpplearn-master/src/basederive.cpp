#include "../inc/basederive.h"

//构造子类同时构造基类部分，调用基类构造函数

double BulkQuote::net_price(std::size_t num) const
{
    cout << "this is BulkQuote net_price" << endl;
    if (num >= min_qty)
    {
        return discount * price * num;
    }
    else
    {
        return num * price;
    }
}

void use_base_static()
{
    Quote::PrintHello();
    BulkQuote::PrintHello();
}

void use_derive_to_base()
{
    BulkQuote bulkquote(string("Live"), 1.2, 100, 0.8);
    //子类传给基类构造函数，或者子类赋值给基类
    //就会调用基类构造函数，只构造基类部分。
    Quote quote(bulkquote);
    quote.printMem();
    quote = bulkquote;
    quote.printMem();
}

/***********
 *
 *
1  派生类向基类转换只在指针或引用时才生效
2  不存在默认的基类向子类转换，但是如果确认转换安全可以通过static_cast来转换。
3  类不想被继承，可以在类名后添加final关键字
4  如果子类无权访问基类构造函数，则无法实现子类对象向基类对象的转换。
5  子类对象可以向基类对象转换，默认只将子类对象中基类的成员赋值给基类对象。
*/

/*
 * 6 多态就是将子类对象的指针赋值给基类对象的指针，通过调用基类的虚函数，实现动态绑定，
 * 运行时调用了子类的虚函数。
 *
 *7 final 声明的虚函数会阻止继承该类的类重写该函数
 *8 override 要求编译器检测重写的函数是否符合规则，是否为虚函数，是否为类型相同。
 *9 继承纯虚类，一定要实现它的所有纯虚方法，否则该类无法使用。
 *10  子类可以使用基类的public和protected成员，子类无法使用基类的private成员
 *11 proteced 和private成员不可被对象的方式访问。
 *12 子类的友元函数可以访问子类的私有变量和受保护变量，但是不能访问基类的受保护变量。
 *13 子类的友元函数可以访问子类自己定义的私有变量，但是不能访问从基类继承而来的私有变量。
 *14 子类和基类有相同名字的成员或者非虚函数非静态的成员函数，在使用的时候默认使用子类的，
 如果想使用基类的需要加上基类名字的作用域。
 *15 如果子类实现的函数和基类的虚函数同名，但是参数类型不同，就不是重写而是隐藏，重写要求子类的函数和
 基类的虚函数类型，名称完全一致。
 *16 针对一个普通的非虚函数的成员函数，子类实现了一个同名的函数，就是覆盖，会隐藏基类的同名函数
 *17 重载是对于一个类来讲，实现了多个同名函数，他们的参数不同。
 */
void print_total(ostream &os, const Quote &quote, std::size_t n)
{
    os << quote.net_price(n) << endl;
}
void use_derive_param()
{
    BulkQuote bulkquote(string("Live"), 1.2, 100, 0.8);
    Quote quote(string("Quote"), 1.2);
    print_total(cout, quote, 100);
    print_total(cout, bulkquote, 100);
}

void use_virtualbase()
{
    DeriveFromBase dfb;
}

void use_probase()
{
    Sneaky sk(11);
    // sk.prot_mem;
    sk.GetMem();
    //调用子类的mem_func(int n)
    sk.mem_func(100);
    ProBase pb;
    //调用基类的mem_func()
    pb.mem_func();
    //基类的mem_func()被覆盖了
    sk.mem_func(1);
    //想使用基类的mem_func()需要添加基类作用域
    sk.ProBase::mem_func();
}

void clobber(Sneaky &s)
{
    s.prot_mem = 100;
    s.self_mem = 1000;
}
//子类友元无法访问基类受保护成员
void clobber(ProBase &b)
{
    // b.prot_mem = 10;
}

void use_hiddenbase()
{
    VD1 vd1;
    //调用基类VBase版本
    vd1.VBase::fcn();
    //调用VD1版本
    vd1.fcn(100);

    VD2 vd2;
    VBase *pvb = &vd1;
    //会调用基类的VBase::fcn()
    pvb->fcn();
    VBase *pvb2 = &vd2;
    //多态调用VD2::fcn()
    pvb2->fcn();

    VD1 *pvd1 = &vd2;
    //调用VD2版本的f2()
    pvd1->f2();
}