#include<algorithm>
#include<iostream>
using namespace std;
class Iter{
public:
//  5种迭代器类型
    typedef random_access_iterator_tag iterator_category;
    typedef int                         value_type;
    typedef int                         difference_type;
    typedef int*                        pointer;
    typedef int&                        reference;
    int x;
    Iter(){x==-1;}
    Iter(int a){x=a;}
    bool operator!=(Iter &i2)const{return i2.x!=x;}
    bool operator==(Iter &i2)const{return i2.x==x;}
    void operator+=(int &b){x+=b;}
    int operator-(const Iter&i2)const{return x-i2.x;}
    int operator*()const{
        std::cout<<"calucuate for x"<<x<<std::endl;
        return x*x;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    std::upper_bound(Iter(0),Iter(100),40).x;


}