#ifndef __CLASS_H__
#define __CLASS_H__
#include <iostream>
using namespace std;
#include <string>
class Sales_data
{
public:
    //通过default实现默认构造
    // Sales_data() = default;
    //显示实现默认构造
    Sales_data() : bookNo(""), units_sold(0), revenue(0.0) {}
    // copy构造，根据Sales_data类型对象构造一个新对象
    Sales_data(const Sales_data &sa);
    Sales_data(const std::string &s) : bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(p * n) {}
    Sales_data(std::istream &is);
    //返回图书号
    std::string isbn() const { return bookNo; }
    //获取平均单价
    double avg_price() const;
    //将一个Sales_data对象合并到当前类对象
    Sales_data &combine(const Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);

private:
    //图书编号
    std::string bookNo;
    //销量
    unsigned units_sold = 0;
    //收入
    double revenue = 0.0;
};
// Sales_data的非成员接口
extern Sales_data add(const Sales_data &, const Sales_data &);
extern std::ostream &print(std::ostream &, const Sales_data &);
extern std::istream &read(std::istream &, Sales_data &);
extern void dealSales();

class Sales_new
{
public:
    Sales_new(const std::string &s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(p * n) {}

    Sales_new() : Sales_new("", 0, 0.0) {}
    // copy构造，根据Sales_new类型对象构造一个新对象
    Sales_new(const Sales_new &sa) : Sales_new(sa.bookNo, sa.units_sold, sa.revenue) {}

    Sales_new(std::istream &is) : Sales_new() { read(is, *this); }
    friend std::istream &read(std::istream &, Sales_new &);

private:
    //图书编号
    std::string bookNo;
    //销量
    unsigned units_sold = 0;
    //收入
    double revenue = 0.0;
};

extern std::istream &read(std::istream &, Sales_new &);

struct Data
{
    int ival;
    string s;
};
#endif