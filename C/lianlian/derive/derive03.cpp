#include<string>
#include<iostream>
using namespace std;
class Quote{
    public:
        Quote()=default;//设置为inline
        //赋值初始化
        Quote(const std::string &book,double sales_price){
            price=sales_price;
            bookNo=book;
        }
        std::string isbn()const{
            return bookNo;
        }
        virtual double net_price(std::size_t n)const{
            cout<<"this is Quote net_price"<<endl;
            return n*price;
        }
        //静态static这个东西好神秘
        static void PrintHello(){
            cout<<"hello world"<<endl;
        }
        Quote(const Quote & quote):bookNo(quote.bookNo),price(quote.price){

            
        }


    private:
        std::string bookNo;
    protected:
        double price=0.0;
};