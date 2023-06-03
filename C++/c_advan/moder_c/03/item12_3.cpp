#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<memory>
using namespace std;
/*



*/
/*



*/
class Base{
public:
    void dowork(Base&);
    void dowork(Base&&w);
    using DataType=std::vector<double>;
    //记住同时左值引用与右值区别在括号后面的&号，左值返回对象的引用。右值返回对象，这点需认真对待
    DataType&data()&{
        cout<<"&data()"<<endl;
        return values;
    }
    DataType data()&&{
        cout<<"data()&&"<<endl;
        return std::move(values);
    }
private:
    DataType values;
};
void t1(){
    Base b;
    auto val1=b.data();//b.data()返回左值 ok
    Base c;
    auto val2=std::move(c).data();//std::move(c)右值。但右值的data函数找不到。于是去找左值的，这个是可以的。
}
void t2(){
    Base b;
    auto val1=b.data();//&data()
    Base c;
    auto val2=std::move(c).data();//data()&&
}
int main(){
    t2();
    return 0;
}