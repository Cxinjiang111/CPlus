/*绝不重新定义继承而来的non-virtual函数

*/
#include<iostream>
using namespace std;
class B{
    public:
        void mf();
};
void B::mf()
{
    cout<<"base mf"<<endl;
}
class D:public B{
    public:
        void mf();
};
void D::mf()
{
    cout<<"D mf()"<<endl;
}
int main()
{
    D d;
    d.mf();
//output D mf()
    return 0;
}