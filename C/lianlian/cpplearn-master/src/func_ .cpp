#include "../inc/func_.h"
#include <iostream>
#include <string>
using namespace std;
size_t count_calls()
{
    //调用结束后，这个值仍然有效
    static size_t ctr = 0;
    return ++ctr;
}

void nochange(int a)
{
    a--;
    cout << a << endl;
}

void change(int *p)
{
    (*p)--;
    cout << *p << endl;
}

void change(int &ra)
{
    ra--;
    cout << ra << endl;
}

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

const string &shorterString(const string &s1, const string &s2)
{
    return s1.size() <= s2.size() ? s1 : s2;
}

string &shorterString(string &s1, string &s2)
{
    auto &r = shorterString(const_cast<const string &>(s1), const_cast<const string &>(s2));
    return const_cast<string &>(r);
}

string ::size_type find_char(const string &s, char c, string::size_type &occurs)
{
    //第一次出现的位置(如果有的话)
    auto ret = s.size();
    //设置表示出现次数的形参的值
    occurs = 0;
    for (decltype(ret) i = 0; i != s.size(); ++i)
    {
        if (s[i] == c)
        {
            if (ret == s.size())
                //记录c第一次出现的位置
                ret = i;

            //出现的次数+1
            ++occurs;
        }
    }
    return ret;
}

// const int ia[]等价于const int * ia
// size表示数组的大小，将它显示地传给函数用于控制对ia元素的访问
void print_array(const int ia[], size_t size)
{
    for (size_t i = 0; i != size; ++i)
    {
        cout << ia[i] << endl;
    }
}

// arr是数组的引用，维度是类型的一部分
void print_arrayref(int (&arr)[10])
{
    for (auto elem : arr)
    {
        cout << elem << endl;
    }
}

void error_msg(initializer_list<string> il)
{
    for (auto beg = il.begin(); beg != il.end(); beg++)
    {
        cout << *beg << " ";
    }
    cout << endl;
}

char &get_val(string &str, string::size_type ix)
{
    return str[ix];
}

void func_declare()
{
    // arrT是一个类型别名，他表示的类型含有10个整数数组
    typedef int arrT[10];
    // arrT的等价声明
    using arrT2 = int[10];
    // func返回一个指向含有10个整数的数组的指针
    arrT *func1(int);
    int(*func2(int i))[10];
    // func接受一个int类型的实参，返回值为一个指针
    //该指针指向含有10个整数的数组
    auto func(int i)->int(*)[10];
}

int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};
//返回一个指针，该指针指向含有5个整数的数组
decltype(odd) *arrPtr(int i)
{
    return (i % 2) ? &odd : &even;
}
void print(const char *cp);
void print(const int *beg, const int *end);
void print(const int ia[], size_t size);
typedef string::size_type sz;
void screen(sz ht = 24, sz wh = 80, char back = ' ')
{
}

constexpr int new_sz() { return 42; }
constexpr int foo = new_sz();
constexpr size_t scale(size_t cnt) { return new_sz() * cnt; }
// pf指向一个函数,该函数的参数是两个const string 的引用，返回bool类型
bool (*pf)(const string &, const string &);
//声明一个名为pf2的函数返回值类型为bool*
bool *pf2(const string &, const string &);
// F是函数类型，不是指针
using F = int(int *, int);
// PF是指针类型
using PF = int (*)(int *, int);
F *f1(int);
PF *f2(int);
int (*f3(int))(int *, int);
auto f4(int) -> int (*)(int *, int);
string::size_type sumLength(const string &, const string &);
//根据形参取值，getFcn函数返回值为指向sumLength的指针
decltype(sumLength) *getFcn(const string &);
