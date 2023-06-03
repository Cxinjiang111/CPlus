#ifndef __SINGLE2_H__
#define __SINGLE2_H__
#include <mutex>
#include <memory>
#include <iostream>
using namespace std;
//通过静态成员变量实现单例
//懒汉式
class Single2
{
private:
    Single2()
    {
    }
    Single2(const Single2 &) = delete;
    Single2 &operator=(const Single2 &) = delete;

public:
    static Single2 &GetInst()
    {
        static Single2 single;
        return single;
    }
};

//通过实现单利类，防止该类被继承
// class SingleDrevie : public Single2
// {
// public:
//     SingleDrevie() : Single2()
//     {
//     }
// };

extern void test_single2();

//饿汉式
class Single2Hungry
{
private:
    Single2Hungry()
    {
    }
    Single2Hungry(const Single2Hungry &) = delete;
    Single2Hungry &operator=(const Single2Hungry &) = delete;

public:
    static Single2Hungry *GetInst()
    {
        if (single == nullptr)
        {
            single = new Single2Hungry();
        }
        return single;
    }

private:
    static Single2Hungry *single;
};

//通过实现单利类，防止该类被继承
// class SingleDrevie : public Single2
// {
// public:
//     SingleDrevie() : Single2()
//     {
//     }
// };

extern void test_single2hungry();

//存在析构隐患的单利模式
class Single2Del
{
private:
    Single2Del()
    {
    }
    Single2Del(const Single2Del &) = delete;
    Single2Del &operator=(const Single2Del &) = delete;

public:
    static Single2Del &GetInst()
    {
        static Single2Del single;
        return single;
    }
};

extern void test_singleDangours();

//懒汉式指针
//即使创建指针类型也存在问题
class SinglePointer
{
private:
    SinglePointer()
    {
    }

    SinglePointer(const SinglePointer &) = delete;
    SinglePointer &operator=(const SinglePointer &) = delete;

public:
    static SinglePointer *GetInst()
    {
        if (single != nullptr)
        {
            return single;
        }

        s_mutex.lock();
        if (single != nullptr)
        {
            s_mutex.unlock();
            return single;
        }
        single = new SinglePointer();
        s_mutex.unlock();
        return single;
    }

private:
    static SinglePointer *single;
    static mutex s_mutex;
};

extern void test_singlelazy();

//利用智能指针解决释放问题
class SingleAuto
{

private:
    SingleAuto()
    {
    }

    SingleAuto(const SingleAuto &) = delete;
    SingleAuto &operator=(const SingleAuto &) = delete;

public:
    ~SingleAuto()
    {
        cout << "single auto delete success " << endl;
    }

    static std::shared_ptr<SingleAuto> GetInst()
    {
        if (single != nullptr)
        {
            return single;
        }

        s_mutex.lock();
        if (single != nullptr)
        {
            s_mutex.unlock();
            return single;
        }
        single = std::shared_ptr<SingleAuto>(new SingleAuto);
        s_mutex.unlock();
        return single;
    }

private:
    static std::shared_ptr<SingleAuto> single;
    static mutex s_mutex;
};

extern void test_singleauto();

// safe deletor
//防止外界delete
//声明辅助类
//该类定义仿函数调用SingleAutoSafe析构函数
//不可以提前声明SafeDeletor，编译时会提示incomplete type
// class SafeDeletor;
//所以要提前定义辅助类
class SingleAutoSafe;
class SafeDeletor
{
public:
    void operator()(SingleAutoSafe *sf)
    {
        cout << "this is safe deleter operator()" << endl;
        delete sf;
    }
};
class SingleAutoSafe
{
private:
    SingleAutoSafe() {}
    ~SingleAutoSafe()
    {
        cout << "this is single auto safe deletor" << endl;
    }
    SingleAutoSafe(const SingleAutoSafe &) = delete;
    SingleAutoSafe &operator=(const SingleAutoSafe &) = delete;
    //定义友元类，通过友元类调用该类析构函数
    friend class SafeDeletor;
    //定义友元函数
    friend void SafeDelFunc(SingleAutoSafe *f);

public:
    static std::shared_ptr<SingleAutoSafe> GetInst()
    {
        if (single != nullptr)
        {
            return single;
        }

        s_mutex.lock();
        if (single != nullptr)
        {
            s_mutex.unlock();
            return single;
        }
        //额外指定删除器
        single = std::shared_ptr<SingleAutoSafe>(new SingleAutoSafe, SafeDeletor());
        //也可以指定删除函数
        // single = std::shared_ptr<SingleAutoSafe>(new SingleAutoSafe, SafeDelFunc);
        s_mutex.unlock();
        return single;
    }

private:
    static std::shared_ptr<SingleAutoSafe> single;
    static mutex s_mutex;
};

extern void test_singleautosafe();

//带模板的通用单例类
template <typename T>
class SafeDeletor_T
{
public:
    void operator()(T *st)
    {
        delete st;
    }
};

template <typename T>
class Single_T
{
protected:
    Single_T() = default;
    Single_T(const Single_T<T> &st) = delete;
    Single_T &operator=(const Single_T<T> &st) = delete;
    ~Single_T()
    {
        cout << "this is auto safe template destruct" << endl;
    }

public:
    static std::shared_ptr<T> GetInst()
    {
        if (single != nullptr)
        {
            return single;
        }

        s_mutex.lock();
        if (single != nullptr)
        {
            s_mutex.unlock();
            return single;
        }
        //额外指定删除器
        single = std::shared_ptr<T>(new T, SafeDeletor_T<T>());
        //也可以指定删除函数
        // single = std::shared_ptr<SingleAutoSafe>(new SingleAutoSafe, SafeDelFunc);
        s_mutex.unlock();
        return single;
    }

private:
    static std::shared_ptr<T> single;
    static mutex s_mutex;
};

//模板类的static成员要放在h文件里初始化
template <typename T>
std::shared_ptr<T> Single_T<T>::single = nullptr;

template <typename T>
mutex Single_T<T>::s_mutex;

//通过继承方式实现网络模块单例
class SingleNet : public Single_T<SingleNet>
{
private:
    SingleNet() = default;
    SingleNet(const SingleNet &) = delete;
    SingleNet &operator=(const SingleNet &) = delete;
    ~SingleNet() = default;
    friend class SafeDeletor_T<SingleNet>;
    friend class Single_T<SingleNet>;
};

extern void
test_singlenet();

#endif