#ifndef __MYSTRING_H__
#define __MYSTRING_H__
#include <iostream>
#include <string>
using namespace std;
extern void use_mystr();
extern void test_share();
extern void swap_int(int &, int &);
extern void use_mystr_1();
class mystring_
{
private:
    /* data */
public:
    mystring_(/* args */);
    mystring_(const mystring_ &mstr);
    mystring_(const char *m_str);
    mystring_(const string);
    ~mystring_();

    friend ostream &operator<<(ostream &os, const mystring_ &mystr1);
    mystring_ &operator=(const mystring_ &mystr);
    mystring_ &operator=(string str);
    mystring_ &operator=(const char *cstr);
    friend mystring_ operator+(const mystring_ &str1, const mystring_ &str2);
    char operator[](unsigned int index);
    friend class mystringOpr_;

private:
    char *m_str;
};

class mystringOpr_
{
public:
    bool operator()(const mystring_ &, const mystring_ &);
};

class HasPtr
{
public:
    HasPtr() = default;
    HasPtr(const string &str);
    ~HasPtr();
    HasPtr(const HasPtr &hp);
    // HasPtr &operator=(const HasPtr &hp);
    friend ostream &operator<<(ostream &os, const HasPtr &);
    friend void swap(HasPtr &, HasPtr &);
    HasPtr &operator=(HasPtr hptr);

private:
    string *m_str;
    int m_index;
    static int _curnum;
};

class SharePtr
{
public:
    //构造函数根据字符串值构造一个字符串指针，并且初始化引用计数为1
    SharePtr(const std::string str = "") : pstr(new string(str)),
                                           usecount(new size_t(1)) {}
    SharePtr(const SharePtr &sptr);
    SharePtr &operator=(const SharePtr &sptr);
    ~SharePtr();
    //输出引用计数
    size_t getUseCount();

private:
    //共享的字符串指针
    string *pstr;
    //引用计数
    size_t *usecount;
};

#endif