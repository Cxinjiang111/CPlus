#include<iostream>
#include<deque>
#include<vector>
#include<typeinfo>
using namespace std;
/*
Know how to view deduced types
*/
 template<typename T>//只对TD进行声明
    class TD;   
    //如果尝试实例化这个类模板就会引出⼀个错误消息，因为这⾥没有⽤来实例化的类模板定义。为了查看x
    //和y的类型，只需要使⽤它们的类型去实例化TD：        

void t1(){
    const int theAnswer=42;
    auto x=theAnswer; //-->int
    auto y=&theAnswer;//-->const int*

    //编译器诊断
    //TD<decltype(x)> xtype;//引出错误消息
    //TD<decltype(y)> yType;//x和y的类型
    //
    cout << typeid(x).name()<<"\n";//显示x和y的类型b i 
    cout << typeid(y).name()<<"\n";//显示x和y的类型  kpi const to konst(const)
}
class widget{
    widget&operator()(){

    };
};
template<typename T>
void f(const T& param);
void t2(){
    std::vector<widget> createvec();
    const auto vw=createvec();
    if(!vw.empty()){
        f(&vw[0]);
    }
}
template<typename T>
void f(const T& param){
    using std::cout;
    cout<<"T       "<<typeid(T).name()<<"\n";
    cout<<"param=  "<<typeid(param).name()<<"\n";
}
int main(){
    //t1();
    t2();
    return 0;

}




