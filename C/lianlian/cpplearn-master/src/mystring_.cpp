#include "../inc/mystring_.h"
#include <cstring>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;
mystring_::mystring_(/* args */) : m_str("")
{
}

mystring_ operator+(const mystring_ &str1, const mystring_ &str2)
{
    size_t len = strlen(str1.m_str) + strlen(str2.m_str) + 1;
    mystring_ strtotal;
    strtotal.m_str = new char[len + 1];
    memset(strtotal.m_str, 0, len);
    memcpy(strtotal.m_str, str1.m_str, strlen(str1.m_str));
    strcat(strtotal.m_str, str2.m_str);
    return strtotal;
}

mystring_::mystring_(const mystring_ &mystr)
{
    if (&mystr == this)
    {
        return;
    }

    if (mystr.m_str == nullptr)
    {
        m_str = nullptr;
        return;
    }
    size_t len = strlen(mystr.m_str);
    m_str = new char[len + 1];
    strcpy(m_str, mystr.m_str);
    m_str[len] = '\0';
}

mystring_::mystring_(const char *mstr)
{
    cout << "use mystring_ construct , param is const char *" << endl;
    size_t len = strlen(mstr);
    m_str = new char[len + 1];
    strcpy(m_str, mstr);
    m_str[len] = '\0';
}

mystring_::mystring_(const string str)
{
    cout << "use mystring_ construct string str" << endl;
    size_t len = str.length();
    m_str = new char[len + 1];
    strncpy(m_str, str.c_str(), len);
    m_str[len] = '\0';
}

mystring_::~mystring_()
{
    if (m_str == "" || m_str == nullptr)
    {
        cout << "begin destruct , str is null or empty" << endl;
    }
    else
    {
        cout << "begin destruct " << m_str << endl;
    }

    if (m_str == nullptr || m_str == "")
    {
        return;
    }

    delete[] m_str;
    m_str = nullptr;
}

mystring_ &mystring_::operator=(const mystring_ &mystr)
{
    if (&mystr == this)
    {
        return *this;
    }

    if (this->m_str != nullptr)
    {
        delete[] m_str;
        this->m_str = nullptr;
    }

    if (mystr.m_str == nullptr)
    {
        m_str = nullptr;
    }

    size_t len = strlen(mystr.m_str);
    m_str = new char[len + 1];
    strcpy(m_str, mystr.m_str);
    m_str[len] = '\0';
    return *this;
}

mystring_ &mystring_::operator=(string str)
{
    cout << "use operator = string str" << endl;
    if (this->m_str != nullptr)
    {
        delete[] m_str;
        this->m_str = nullptr;
    }

    size_t len = str.length();
    m_str = new char[len + 1];
    strncpy(m_str, str.c_str(), len);
    m_str[len] = '\0';
    return *this;
}

mystring_ &mystring_::operator=(const char *cstr)
{
    cout << "use operator = const char*" << endl;
    if (this->m_str != nullptr)
    {
        delete[] m_str;
        this->m_str = nullptr;
    }

    size_t len = strlen(cstr);
    m_str = new char[len + 1];
    strncpy(m_str, cstr, len);
    m_str[len] = '\0';
    return *this;
}

ostream &operator<<(ostream &os, const mystring_ &mystr1)
{
    if (mystr1.m_str == nullptr)
    {
        os << "mystring_ data is null" << endl;
        return os;
    }
    os << "mystring_ data is " << mystr1.m_str << endl;
    return os;
}

char mystring_::operator[](unsigned int index)
{
    if (index >= strlen(m_str))
    {
        throw "index out of range!!!";
    }

    return m_str[index];
}

bool mystringOpr_::operator()(const mystring_ &str1, const mystring_ &str2)
{
    if (strlen(str1.m_str) > strlen(str2.m_str))
    {
        return true;
    }

    if (strlen(str1.m_str) < strlen(str2.m_str))
    {
        return false;
    }

    for (unsigned int i = 0; i < strlen(str1.m_str); i++)
    {
        return str1.m_str[i] > str2.m_str[i];
    }
}

void use_mystr_1()
{
    auto mystr1 = mystring_("hello zack");
    auto mystr2(mystr1);
    auto mystr3 = mystring_();
    cout << mystr1 << mystr2 << mystr3 << endl;
    mystring_ mystr4 = ", i love u";
    auto mystr5 = mystr1 + mystr4;
    cout << "mystr4 is " << mystr4 << endl;
    cout << "mystr5 is " << mystr5 << endl;

    mystring_ mystr6 = "";
    auto mystr7 = mystr5 + mystr6;
    cout << "mystr7 is " << mystr7 << endl;

    auto ch = mystr1[4];
    cout << "index is 4, char is " << ch << endl;

    std::vector<mystring_> vec_mystring_;
    vec_mystring_.push_back(mystr1);
    vec_mystring_.push_back(mystr2);
    vec_mystring_.push_back(mystr3);
    vec_mystring_.push_back(mystr4);
    vec_mystring_.push_back(mystr5);
    vec_mystring_.push_back(mystr6);
    vec_mystring_.push_back(mystr7);
    sort(vec_mystring_.begin(), vec_mystring_.end(), mystringOpr_());
    cout << "====================after sort ..." << endl;
    for_each(vec_mystring_.begin(), vec_mystring_.end(), [](const mystring_ &str)
             { cout << str << endl; });
}

void use_mystr_2()
{
    //直接初始化
    mystring_ mystr1("hello zack");
    //直接初始化
    auto mystr2(mystr1);
    //拷贝初始化
    auto mystr3 = mystr2;
    //拷贝初始化
    mystring_ mystr4 = "hello world!";
    //拷贝初始化
    auto mystr5 = mystring_("hello everyone");
    cout << mystr1 << mystr2 << mystr3 << mystr4 << mystr5 << endl;
}

HasPtr f(HasPtr hp)
{
    HasPtr copyptr = hp;
    return copyptr;
}

void use_mystr_3()
{
    HasPtr ptr("hello zack!");
    f(ptr);
}

void use_mystr()
{
    HasPtr hasptr1("hello zack");
    cout << hasptr1 << endl;
    HasPtr hasptr2(hasptr1);
    cout << hasptr2 << endl;
    HasPtr hasptr3 = hasptr2;
    cout << hasptr3 << endl;
    HasPtr hasptr4("hello world");
    hasptr4 = hasptr3;
    cout << hasptr4 << endl;
}

HasPtr::HasPtr(const string &str) : m_str(new string(str)), m_index(++_curnum)
{
    cout << "this is param constructor" << endl;
}
int HasPtr::_curnum = 0;
HasPtr::~HasPtr()
{
    if (m_str != nullptr)
    {
        delete m_str;
        m_str = nullptr;
    }
}

HasPtr::HasPtr(const HasPtr &hp)
{
    cout << "this is copy construtor" << endl;
    if (&hp != this)
    {
        this->m_str = new string(string(*hp.m_str));
        int seconds = time((time_t *)NULL);
        _curnum++;
        this->m_index = _curnum;
    }

    return;
}

// HasPtr &HasPtr::operator=(const HasPtr &hp)
// {
//     cout << "this is operator = " << endl;
//     if (&hp != this)
//     {
//         this->m_str = new string(string(*hp.m_str));
//         this->m_index = hp.m_index;
//     }

//     return *this;
// }

HasPtr &HasPtr::operator=(HasPtr hptr)
{
    // hptr是一个局部变量
    //交换后hptr.m_str指向this.m_str原来指向的内存
    swap(*this, hptr);
    // return返回*this后，hptr自动被回收
    return *this;
}

void swap(HasPtr &hptr1, HasPtr &hptr2)
{
    using std::swap;
    swap(hptr1.m_index, hptr2.m_index);
    swap(hptr1.m_str, hptr2.m_str);
}

ostream &operator<<(ostream &os, const HasPtr &hp)
{
    os << "index is " << hp.m_index << " , data is " << *(hp.m_str) << endl;
    return os;
}

SharePtr::SharePtr(const SharePtr &sptr)
{
    //如果是自赋值则跳过
    if (&sptr == this)
    {
        return;
    }
    //其他类对象拷贝给自己
    this->pstr = sptr.pstr;
    //引用计数增加
    (*sptr.usecount)++;
    //拷贝对方的引用计数给自己
    this->usecount = sptr.usecount;
}

SharePtr &SharePtr::operator=(const SharePtr &sptr)
{
    //如果是自赋值则跳过
    if (&sptr == this)
    {
        return *this;
    }

    //减少自己原来的引用计数
    (*this->usecount)--;

    //判断引用计数是否为0
    if (*(this->usecount) == 0)
    {
        //回收原来指向的内存
        delete (this->pstr);
        //回收引用计数内存
        delete (this->usecount);
    }

    //其他类对象拷贝给自己
    this->pstr = sptr.pstr;

    //对方引用计数增加
    (*sptr.usecount)++;
    //拷贝对方的引用计数给自己
    this->usecount = sptr.usecount;
    return *this;
}

SharePtr::~SharePtr()
{
    //引用计数-1
    (*this->usecount)--;
    //引用计数为0，销毁内存
    if (*(this->usecount) == 0)
    {
        cout << "use count is 0 dealloc"
             << endl;
        delete usecount;
        delete pstr;
        return;
    }
}

//获取引用计数
size_t SharePtr::getUseCount()
{
    return *(this->usecount);
}

void test_share()
{
    SharePtr sptr1("hello zack");
    SharePtr sptr2(sptr1);
    cout << "sptr1 use count is "
         << sptr1.getUseCount() << endl;
    cout << "sptr2 use count is "
         << sptr2.getUseCount() << endl;
    SharePtr sptr3("hello world");
    cout << "sptr3 use count is "
         << sptr3.getUseCount() << endl;
    sptr2 = sptr3;
    cout << "sptr1 use count is "
         << sptr1.getUseCount() << endl;
    cout << "sptr2 use count is "
         << sptr2.getUseCount() << endl;
    cout << "sptr3 use count is "
         << sptr3.getUseCount() << endl;
}

void swap_int(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
