#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool compare(int a, int b)
{
	return  a < b;
}
void test1()
{
    vector<int> myvec{3, 2, 5, 7, 3, 2 };
    std::vector<int> lbvec(myvec);
    sort(lbvec.begin(),lbvec.end(),compare);

    sort(myvec.begin(),myvec.end(),[](int a,int b)->bool{
        return a<b;
    });
}
//五、捕获外部变量
void test2()
{
    int a=123;
    auto f=[a](){cout<<a<<endl;};//这句仅仅捕获外部变量
    f();
    cout<<a<<endl;
    //法二 仅仅局部lambda内修改变量值，相当于函数值传递
    [](int a){std::cout<<a<<std::endl;}(456);
    cout<<a<<endl;
    //以引用的方式传递，这样就可以修改内部的值
    auto f3=[](int& a){
        a=234;
        std::cout<<a<<std::endl;};
    f3(a);
    cout<<a<<endl;
}
//5.1 值捕获
/*
值捕获和参数传递中的值传递类似，被捕获的变量的值在 Lambda 
表达式创建时通过值拷贝的方式传入，因此随后在外部对该变量的
修改不会影响Lambda表达式中的值，所以a还是123。
*/
void t3()
{
    int a = 123; 
    //这种相当于传入const类型的值
    auto f = [a] { std::cout << a << std::endl; }; 
    a = 321;
    f(); // 输出：123
}
//5.2 引用捕获
/*
从示例中可以看出，引用捕获的变量使用的实际上就是该引用所绑定的对象，故输出的为 321
*/
void t4()
{
    int a=123;
    //这种相当于引用所绑定的对象
    auto f=[&a]{cout<<a<<endl;};
    a=321;
    f();//此时才调用，在
}
//5.3 隐式捕获
void t5()
{
    int a = 123;
    auto f = [=] { cout << a << endl; };    // 值捕获
    a = 321;    
    f(); // 输出：123
}
void t6()
{
    int a = 123;
    auto f = [&] { cout << a << endl; };    // 引用捕获
    a = 321;
    f(); // 输出：321
}
//5.5 修改捕获变量
void t7()
{
    int a=123;
    auto f=[a]()mutable{
        a++;   //局部利用这个值，并在该局部内修改这个值，起始就是相当于值传递，给予了修改该变量的机会
    };
    cout<<a<<endl;//123
    f();//124
    cout<<a<<endl;//123
}
int main()
{
    //test2();
    //t3();
    //t4();
    t7();
    return 0;
}

