#ifndef __BASE_DERIVE_H__
#define __BASE_DERIVE_H__
#include <string>
#include <iostream>
using namespace std;
class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price)
    {
        price = sales_price;
        bookNo = book;
    }
    std::string isbn() const
    {
        return bookNo;
    }
    virtual double net_price(std::size_t n) const
    {
        cout << "this is Quote net_price" << endl;
        return n * price;
    }
    static void PrintHello()
    {
        cout << "hello world" << endl;
    }
    Quote(const Quote &quote) : bookNo(quote.bookNo), price(quote.price) {}

    void printMem()
    {
        cout << "price is " << price << " bookNo is " << bookNo << endl;
    }
    virtual ~Quote()
    {
        cout << "this is Quote destruct" << endl;
    }
    // final 阻止其他继承Quote的类重写f3函数
    virtual void f3() final {}
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class BulkQuote : public Quote
{
public:
    BulkQuote() = default;
    BulkQuote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc)
    {
    }

    // override 是C11提供的继承关系检测工具，检测函数类型是否匹配，是否为虚函数等。
    double net_price(std::size_t) const override;
    // void f3() {}

private:
    //打折后最多买多少
    std::size_t min_qty = 0;
    //折扣额度
    double discount = 0.0;
};

extern void use_base_static();
extern void use_derive_to_base();
extern void use_derive_param();

//纯虚类
class VirtualBase
{
public:
    VirtualBase() = default;
    virtual void mem() = 0;
    virtual void test() = 0;
};

class DeriveFromBase : public VirtualBase
{
    virtual void mem()
    {
    }
    virtual void test() {}
};

extern void use_virtualbase();

// protected
class ProBase
{
public:
    ProBase() = default;
    ProBase(int n) : prot_mem(n) {}
    void mem_func()
    {
        cout << "this is ProBase mem_func" << endl;
    }

protected:
    int prot_mem;

private:
    int priv_mem;
};

class Sneaky : public ProBase
{
public:
    Sneaky() = default;
    Sneaky(int n) : ProBase(1024), prot_mem(n) {}
    //子类可以使用基类的public和protected成员
    void UsePro()
    {
        cout << prot_mem << endl;
    }

    //子类无法使用基类的private成员。
    // void UsePriv()
    // {
    //     cout << priv_mem << endl;
    // }
    friend void clobber(Sneaky &);
    friend void clobber(ProBase &);

    void GetMem()
    {
        cout << "this is ProBase prot_mem: " << ProBase::prot_mem << endl;
        cout << "this is Sneaky prot_mem: " << prot_mem << endl;
    }

    void mem_func(int n)
    {
        cout << "this is Sneaky mem_func" << endl;
    }

private:
    int self_mem;
    int prot_mem;
};

extern void use_probase();

class VBase
{
public:
    virtual int fcn()
    {
        cout << "this is VBase fcn()" << endl;
    }
};

class VD1 : public VBase
{
public:
    // VD1自己定义的fcn(int)，因为和基类VBase的fcn参数不同
    //但是VD1也继承了VBase  fcn()这个版本
    //隐藏了基类的fcn()
    int fcn(int)
    {
        cout << "this is VD1 fcn(int)" << endl;
    }

    // VD1自己新定义的虚函数
    virtual void f2()
    {
        cout << "this is VD1 f2()" << endl;
    }
};

class VD2 : public VD1
{
public:
    //隐藏了VD1版本的fcn(int),因为VD1中fcn(int)不是虚函数
    int fcn(int)
    {
        cout << "this is VD2 fcn(int)" << endl;
    }

    //重写,因为VD1从VBase中继承了虚函数fcn()
    int fcn()
    {
        cout << "this is VD2 fcn()" << endl;
    }

    //重写了VD1的虚函数

    void f2()
    {
        cout << "this is VD2 f2()" << endl;
    }
};

extern void use_hiddenbase();
#endif