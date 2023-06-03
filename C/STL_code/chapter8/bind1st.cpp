#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
void print(int t,std::string sparator)
{
    std::cout<<t<<sparator;
}
int main()
{
    std::vector<int> element{1,2,3,4,5};
    std::string delim="\n";
    for_each(element.begin(),element.end(),std::bind2nd(std::ptr_fun(& print),delim));


}