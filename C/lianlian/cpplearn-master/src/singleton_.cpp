#include "../inc/singleton_.h"
#include <thread>

shared_ptr<Singleton_> Singleton_::_inst = nullptr;
mutex Singleton_::_mutex;

void test_single()
{
    shared_ptr<Singleton_> inst1 = Singleton_::getinstance();
    cout << "inst1 get ptr is " << inst1.get() << endl;

    shared_ptr<Singleton_> inst2 = Singleton_::getinstance();
    cout << "inst2 get ptr is " << inst2.get() << endl;
}

void thread_func(int i)
{
    cout << "this is thread " << i << endl;
    shared_ptr<Singleton_> inst = Singleton_::getinstance();
    cout << "inst ptr is " << inst.get() << endl;
}

void test_thread_single()
{
    for (int i = 0; i < 3; i++)
    {
        thread tid(thread_func, i + 1);
        tid.join();
    }
    cout << "main thread exit " << endl;
}