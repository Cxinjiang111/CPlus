#include "../inc/pointer_.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <memory>
#include <exception>
using namespace std;
void use_pointer()
{
    //开辟整形指针，指向一个值为5的元素
    int *pint = new int(5);
    //开辟指向字符串的指针
    string *pstr = new string("hello zack");
    //释放pint指向的空间
    if (pint != nullptr)
    {
        delete pint;
        pint = nullptr;
    }
    //释放指针指向的空间。
    if (pstr != nullptr)
    {
        delete pstr;
        pstr = nullptr;
    }
}

void use_sharedptr()
{
    //定义一个指向int类型的shared_ptr
    shared_ptr<int> psint;
    //定义一个指向string类型的shared_ptr
    shared_ptr<string> psstr;
    //定义一个指向list<int>的shared_ptr
    shared_ptr<list<int>> psilist;
    //我们定义一个指向整形5得指针
    auto psint2 = make_shared<int>(5);
    //判断智能指针是否为空
    if (psint2 != nullptr)
    {
        cout << "*psint2 is " << *psint2 << endl;
    }

    auto psstr2 = make_shared<string>("hello zack");
    if (psstr2 != nullptr && !psstr2->empty())
    {
        cout << "*psstr2 is " << *psstr2 << endl;
    }

    int *pint = psint2.get();
    cout << "*pint  is " << *pint << endl;
    //将psint2赋值给psint3,他们底层的内置指针相同
    // psint3和psint2引用计数相同，引用计数+1，都为2
    shared_ptr<int> psint3 = psint2;
    //打印引用计数
    cout << "psint2 usecount is " << psint2.use_count() << endl;
    cout << "psint3 usecount is " << psint3.use_count() << endl;
    // psint3引用计数为1
    psint3 = make_shared<int>(1024);
    // psint2引用计数-1，变为1
    //打印引用计数
    cout << "psint2 usecount is " << psint2.use_count() << endl;
    cout << "psint3 usecount is " << psint3.use_count() << endl;
}

StrBlob::StrBlob()
{
    data = make_shared<vector<string>>();
}

StrBlob::StrBlob(const StrBlob &sb)
{
    data = sb.data;
}

StrBlob::StrBlob(const initializer_list<string> &li)
{
    data = make_shared<vector<string>>(li);
}

StrBlob &StrBlob::operator=(const StrBlob &sb)
{
    if (&sb != this)
    {
        this->data = sb.data;
    }

    return *this;
}

//检测i是否越界
void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
    {
        throw out_of_range(msg);
    }
}

string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string &StrBlob::back()
{
    check(0, "back on empty StrBlog");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "back on pop_back StrBlog");
    data->pop_back();
}

void StrBlob::printCount()
{
    cout << "shared_ptr use count is " << data.use_count() << endl;
}

void test_StrBlob()
{
    StrBlob strblob1({"hello", "zack", "good luck"});
    StrBlob strblob2;
    try
    {
        auto str2front = strblob2.front();
    }
    catch (std::out_of_range &exc)
    {
        cout << exc.what() << endl;
    }
    catch (...)
    {
        cout << "unknown exception" << endl;
    }

    strblob2 = strblob1;
    auto str1front = strblob1.front();
    cout << "strblob1 front is " << str1front << endl;

    strblob2.printCount();
    strblob1.printCount();
}

void delfunc(string *p)
{
    if (p != nullptr)
    {
        delete (p);
        p = nullptr;
    }

    cout << "self delete" << endl;
}

void shared_ptrnew()
{
    auto psint = shared_ptr<int>(new int(5));
    auto psstr = shared_ptr<string>(new string("hello zack"));
    //错误，不能用内置指针隐式初始化shared_ptr
    // shared_ptr<int> psint2 = new int(5);
    //正确，显示初始化
    shared_ptr<string> psstr2(new string("good luck"));
    //可以通过一个shared_ptr 构造另一个shared_ptr
    shared_ptr<string> psstr3(psstr2);
    cout << "psstr2 use count is " << psstr2.use_count() << endl;
    cout << "psstr3 use count is " << psstr3.use_count() << endl;
    //可以设置新的删除函数替代delete
    shared_ptr<string> psstr4(new string("good luck for zack"), delfunc);
}

void process(shared_ptr<int> psint)
{
    cout << "psint data is " << *psint << endl;
}

void bad_use_sharedptr2()
{
    int *p = new int(5);
    process(shared_ptr<int>(p));
    //危险，p已经被释放，会造成崩溃或者逻辑错误
    cout << "p data is " << *p << endl;
}

void bad_use_sharedptr3()
{
    shared_ptr<int> p(new int(5));
    //通过p获取内置指针q
    //注意q此时被p绑定，不要手动delete q
    int *q = p.get();
    {
        //两个独立的shared_ptr m和p都绑定q
        auto m = shared_ptr<int>(q);
    }

    //上述}结束则m被回收，其绑定的q也被回收
    //此时使用q是非法操作，崩溃或者逻辑错误
    cout << "q data is " << *q << endl;
}

void good_use_sharedptr()
{
    shared_ptr<int> p(new int(5));
    //通过p获取内置指针q
    //注意q此时被p绑定，不要手动delete q
    int *q = p.get();
    {
        // m和p的引用计数都为2
        shared_ptr<int> m(p);
    }

    //上述}结束则m被回收，其绑定的q也被回收
    //此时使用q是非法操作，崩溃或者逻辑错误
    cout << "q data is " << *q << endl;
}

void reset_shared()
{
    shared_ptr<int> p(new int(5));
    // p重新绑定新的内置指针
    p.reset(new int(6));
    //如果引用计数为1，unique返回true
    if (!p.unique())
    {
        //还有其他人引用，所以我们为p指向新的内存
        p.reset(new int(6));
    }

    // p目前是唯一用户
    *p = 1024;
}

void execption_shared()
{
    shared_ptr<string> p(new string("hello zack"));
    //此处导致异常
    int m = 5 / 0;
    //即使崩溃也会保证p被回收
}

void delfuncint(int *p)
{
    cout << *p << " in del func" << endl;
}

void delfunc_shared()
{
    int p = 6;
    shared_ptr<int> psh(&p, delfuncint);
}

void use_uniqueptr_p()
{
    //指向double类型的unique指针
    unique_ptr<double> udptr;
    //一个指向int类型的unique指针
    unique_ptr<int> uiptr(new int(42));
    // unique不支持copy
    // unique_ptr<int> uiptr2(uiptr);
    // unique不支持赋值
    // unique_ptr<int> uiptr3 = uiptr;
}

void use_uniqueptr_reset()
{
    //定义一个upstr
    unique_ptr<string> upstr(new string("hello zack"));
    // upstr.release()返回其内置指针，并将upstr置空
    // 用upstr返回的内置指针初始化了upstr2
    unique_ptr<string> upstr2(upstr.release());
    unique_ptr<string> upstr3(new string("hello world"));
    //将upstr3的内置指针转移给upstr2
    // upstr2放弃原来的内置指针，指向upstr3返回的内置指针。
    upstr2.reset(upstr3.release());
}

void use_uniqueptr_del()
{
    //定义一个upstr
    unique_ptr<string> upstr(new string("hello zack"));
    //获取upstr的内置指针
    string *inerp = upstr.release();
    //因为此时upstr已经通过release交出内置指针使用权
    //所以要手动释放内置指针的内存
    delete inerp;
}

unique_ptr<int> clone_unique(int a)
{
    return unique_ptr<int>(new int(a));
}

void use_uniqueptr_clone()
{
    int a = 1024;
    unique_ptr<int> mp = clone_unique(a);
    cout << *mp << endl;
}

void unique_deleter(int *p)
{
    cout << "this is unique deleter" << endl;
    cout << "inner pointer data is " << *p << endl;
}

void use_uniqueptr()
{
    unique_ptr<int, decltype(unique_deleter) *> mp(new int(1024), unique_deleter);
}

void use_weakptr_count()
{
    //构造shared_ptr
    auto psint = make_shared<int>(1024);
    //用shared_ptr构造weak_ptr
    weak_ptr<int> pwint(psint);
    //打印shared_ptr的引用计数
    cout << "shared_ptr use count is " << psint.use_count() << endl;
}

weak_ptr<int> clone_weakptr(int num)
{
    shared_ptr<int> psint(new int(num));
    return weak_ptr<int>(psint);
}

void use_weakptr_expired()
{
    auto wptr = clone_weakptr(1024);
    if (wptr.expired())
    {
        cout << "wptr inner pointer has been deleted" << endl;
    }
    else
    {
        cout << "wptr inner pointer data is " << *(wptr.lock()) << endl;
    }
}

void use_weakptr()
{
    shared_ptr<int> psint(new int(1022));
    //也可以通过赋值，将shared_ptr赋值给weak_ptr
    weak_ptr<int> pwint = psint;
    //通过weak_ptr生成shared_ptr
    shared_ptr<int> psint2 = pwint.lock();
    cout << "psint use count is " << psint.use_count() << endl;
    cout << "psint2 use count is " << psint2.use_count() << endl;
}