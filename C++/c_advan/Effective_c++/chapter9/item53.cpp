/*不要忽视编译器的警告

*/
#include<iostream>
using namespace std;
class B{
public :
    B(){};
    virtual void f()const;
};
void B::f()const
{
    cout<<"B::f"<<endl;
}
class D:public B{
public:
    D(){};
    virtual void f();
};

void D::f()
{
    cout<<"D::f"<<endl;
}
int main()
{
    D d;
    d.f();
    B b;
    b.f();

    B *pb=new D();
    pb->f();
    /*这个没有警告！！！
D::f
B::f
B::f
    */
    return 0;
}