#ifndef __SINGLETON_H__
#define __SINGLETON_H__
#include <iostream>
#include <string>
#include <memory>
#include <mutex>
using namespace std;
class Singleton_
{
public:
    Singleton_(const Singleton_ &) = delete;
    Singleton_ &operator=(const Singleton_ &) = delete;

    static shared_ptr<Singleton_> &getinstance()
    {
        //如果非空直接返回不加锁节省效率
        if (_inst != nullptr)
        {
            return _inst;
        }
        //最好做一个二次判断
        _mutex.lock();
        if (_inst != nullptr)
        {
            _mutex.unlock();
            return _inst;
        }
        _inst = shared_ptr<Singleton_>(new Singleton_());
        _mutex.unlock();
        return _inst;
    }

private:
    Singleton_() {}
    static shared_ptr<Singleton_> _inst;
    static mutex _mutex;
};
extern void test_single();
extern void test_thread_single();
#endif