#ifndef __MONEY_C_H__
#define __MONEY_C_H__
#include <string>
using namespace std;
typedef double Money;
class Account
{
public:
    Money balance() { return bal; }
    void setbalance(Money bal)
    {
        this->bal = bal;
    }

private:
    Money bal;
};

class ConstRef
{
public:
    ConstRef(int ii) : ci(ii), ri(ii) { i = ii; };

private:
    int i;
    const int ci;
    int &ri;
};
#endif