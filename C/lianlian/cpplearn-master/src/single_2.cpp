#include "../inc/single_2.h"
#include <iostream>
#include <thread>
using namespace std;
//懒汉式
//在类的cpp文件定义static变量
SinglePointer *SinglePointer::single = nullptr;
std::mutex SinglePointer::s_mutex;

// 智能指针方式
std::shared_ptr<SingleAuto> SingleAuto::single = nullptr;
mutex SingleAuto::s_mutex;

//智能指针初始化为nullptr
std::shared_ptr<SingleAutoSafe> SingleAutoSafe::single = nullptr;
mutex SingleAutoSafe::s_mutex;

//也可以定义删除函数
void SafeDelFunc(SingleAutoSafe *f)
{
    delete f;
}

//饿汉式初始化
Single2Hungry *Single2Hungry::single = Single2Hungry::GetInst();
void test_single2()
{
    //多线程情况下可能存在问题
    cout << "s1 addr is " << &Single2::GetInst() << endl;
    cout << "s2 addr is " << &Single2::GetInst() << endl;
}

void thread_func_s2(int i)
{
    cout << "this is thread " << i << endl;
    cout << "inst is " << Single2Hungry::GetInst() << endl;
}

void test_single2hungry()
{
    cout << "s1 addr is " << Single2Hungry::GetInst() << endl;
    cout << "s2 addr is " << Single2Hungry::GetInst() << endl;

    for (int i = 0; i < 3; i++)
    {
        thread tid(thread_func_s2, i);
        tid.join();
    }
}

void thread_func_lazy(int i)
{
    cout << "this is lazy thread " << i << endl;
    cout << "inst is " << SinglePointer::GetInst() << endl;
}

void test_singlelazy()
{
    for (int i = 0; i < 3; i++)
    {
        thread tid(thread_func_lazy, i);
        tid.join();
    }

    //何时释放new的对象？造成内存泄漏
}

void test_singleDangours()
{
    cout << "s1 addr is " << &Single2Del::GetInst() << endl;
    cout << "s2 addr is " << &Single2Del::GetInst() << endl;

    //如果外层不小心delete会出现问题
    auto pinst1 = &Single2Del::GetInst();
    // delete会造成崩溃
    // delete pinst1;

    //多次delete
    auto sp1 = SinglePointer::GetInst();
    auto sp2 = SinglePointer::GetInst();
    cout << "sp1  is  " << sp1 << endl;
    cout << "sp2  is  " << sp2 << endl;

    //什么时候释放是个问题
    delete sp1;
    //二次释放造成崩溃
    // delete sp2;
}

void test_singleauto()
{
    auto sp1 = SingleAuto::GetInst();
    auto sp2 = SingleAuto::GetInst();
    cout << "sp1  is  " << sp1 << endl;
    cout << "sp2  is  " << sp2 << endl;
    //此时存在隐患，可以手动删除裸指针，造成崩溃
    // delete sp1.get();
}

void test_singleautosafe()
{
    auto sp1 = SingleAutoSafe::GetInst();
    auto sp2 = SingleAutoSafe::GetInst();
    cout << "sp1  is  " << sp1 << endl;
    cout << "sp2  is  " << sp2 << endl;
    //此时无法访问析构函数，非常安全
    // delete sp1.get();
}

void test_singlenet()
{
    auto sp1 = SingleNet::GetInst();
    auto sp2 = SingleNet::GetInst();
    cout << "sp1  is  " << sp1 << endl;
    cout << "sp2  is  " << sp2 << endl;
}