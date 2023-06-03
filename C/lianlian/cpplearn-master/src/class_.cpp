#include "../inc/class_.h"
#include <iostream>
using namespace std;
void dealSales()
{
    //保存当前求和结果的变量
    Sales_data total;
    //读入第一笔交易
    if (read(cin, total))
    {
        //保存下一条交易数据的变量
        Sales_data trans;
        //读入下一条交易数据
        while (read(cin, trans))
        {
            //判断isbn
            if (total.isbn() == trans.isbn())
            {
                //更新变量total的值
                total.combine(trans);
            }
            else
            {
                //输出结果
                print(cout, total) << endl;
                // isbn号不一样，说明是新类型的书
                //  处理新类型的书
                total = trans;
            }
        }
        //输出最后一条交易
        print(cout, total) << endl;
    }
    else
    {
        //没有输出任何信息
        cerr << "No data?!" << endl;
    }
}

double Sales_data::avg_price() const
{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Sales_data::Sales_data(const Sales_data &sa)
{
    this->bookNo = sa.bookNo;
    this->revenue = sa.revenue;
    this->units_sold = sa.units_sold;
}

Sales_data::Sales_data(std::istream &is)
{
    read(is, *this);
}

Sales_data &Sales_data::combine(const Sales_data &sa)
{
    this->units_sold += sa.units_sold;
    this->revenue += sa.revenue;
    //返回调用该函数的对象
    return *this;
}

Sales_data add(const Sales_data &sa1, const Sales_data &sa2)
{
    Sales_data total = sa1;
    total.combine(sa2);
    return total;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

std::istream &read(std::istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    return is;
}

std::istream &read(std::istream &is, Sales_new &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    return is;
}