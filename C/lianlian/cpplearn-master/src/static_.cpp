#include "../inc/static_.h"

double Account::interestRate;

void Account::rate(double ds)
{
    interestRate = ds;
}

double Account::initRate()
{
    interestRate = 0.1;
    return interestRate;
}
