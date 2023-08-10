#include<iostream>
#include<string>
using namespace std;
class A
{
private:
    string m_name;
public:
    void printOwing(double amount)
    {
        printBanner();
        std::cout<<"name"<<std::endl;
        std::cout<<"amount"<<amount<<std::endl;

        printDetails(amount);
    }
    void printBanner();
    //改进
    void printDetails(double amount)
    {
        std::cout<<"name"<<std::endl;
        std::cout<<"amount"<<amount<<std::endl;
    }
};

