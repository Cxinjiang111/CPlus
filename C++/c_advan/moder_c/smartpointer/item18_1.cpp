#include<iostream>
#include<memory>
#include<vector>
using namespace std;
void t1(){
    unique_ptr<int>pint(new int(5));
    cout<<*pint;
}
//unique_ptr 没有copy构造函数，不支持普通的拷贝和赋值操作。
void t2(){
    unique_ptr<int>pint(new int(5));
    //unique_ptr<int>pint2(pint); error
    unique_ptr<int>pint2(std::move(pint));
    //cout<<*pint<<endl;//Segmentation fault (core dumped)
    cout<<*pint2<<endl;
}
unique_ptr<int> clone(int p){
    unique_ptr<int>pint(new int(p));
    return pint;
}
//unique_ptr不支持拷贝操作，但却有一个例外：可以从函数中返回一个unique_ptr。
void t3(){
    int p=5;
    unique_ptr<int> pint=clone(p);
    cout<< *pint<<endl;
}//函数指向完 自动释放资源
void fun(){
    int *p=new int(5);

    //catch throw

    delete p;
}
/*
这是我们传统的写法：当我们动态申请内存后，有可能我们接下来的代码由于抛出异常或者提前退出（if语句）而没有执行delete操作。

解决的方法是使用 unique_ptr 来管理动态内存，只要 unique_ptr 指针创建成功，其析构函数都会被调用，确保动态资源被释放。
*/
void t4(){
    vector<unique_ptr<int>> vec;
    unique_ptr<int> p(new int(5));
    vec.push_back(std::move(p));//这里必须用move

}
int main(){
    //t1();
    //t2();
    t3();
    return 0;
}