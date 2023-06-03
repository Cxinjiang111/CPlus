#include "../inc/template_.h"
#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>
#include <cxxabi.h>
using namespace std;

/*
1 typename 定义模板类型，可以定义多个类型，中间用，隔开
template<typename T, typename U>
2  非类型参数 用已知类型定义变量  template<unsigned U, unsigned M>
3



*/

void use_template()
{
    int res = compare(3, 4);
    cout << "compare(3,4) res is " << res << endl;

    vector<int> v1 = {1, 3, 5};
    vector<int> v2 = {2, 4};
    res = compare(v1, v2);
    cout << "compare(v1, v2) res is " << res << endl;

    printData(3.4, "hello world");

    res = compareArray("hello zack", "nice to meet u");
    cout << "compareArray("
         << "hello zack "
         << ", nice to meet u"
         << ") res is " << res << endl;
}

void string_upper(std::string &str)
{
    for_each(str.begin(), str.end(), [](char &c)
             {
        if(c <= 'z' && c >= 'a'){
            c = c - 32;
        } });
}

void use_classtemp()
{
    Blob<int> ia;
    Blob<int> ia2 = {0, 1, 2, 3, 5};
    Blob<string> ia3 = {"hello ", "zack", "nice"};
    for (size_t i = 0; i < ia2.size(); i++)
    {
        ia2[i] = i * i;
    }

    for (size_t i = 0; i < ia2.size(); i++)
    {
        cout << ia2[i] << endl;
    }

    for (size_t i = 0; i < ia3.size(); i++)
    {
        string_upper(ia3[i]);
    }

    for (size_t i = 0; i < ia3.size(); i++)
    {
        cout << ia3[i] << endl;
    }

    const auto &data = ia3.back();
    cout << data << endl;

    ia3.pop_back();
    const auto &data2 = ia3.back();
    cout << data2 << endl;
}

void use_debugdel()
{
    double *p = new double;
    DebugDelete d;
    //调用DebugDelete的仿函数,delete p
    d(p);
    //析构多种类型
    int *np = new int;
    //构造DebugDelete对象后调用仿函数析构np
    DebugDelete()(np);
    //作为删除器析构智能指针
    // p 被delete时会执行DebugDelete的仿函数进行析构
    unique_ptr<int, DebugDelete> p3(new int, DebugDelete());
    // 用DebugDelete 的仿函数析构string的指针
    unique_ptr<string, DebugDelete> sp(new string, DebugDelete());
}

void use_tempmemfunc()
{
    int ia[] = {0, 1, 2, 3, 4};
    vector<long> vi = {7, 6, 5, 4};
    list<const char *> w = {"now", "zack", "lov u"};
    // Blob<T> T被实例化为int，
    //函数模板It被实例化为 int *
    Blob<int> a1(begin(ia), end(ia));
    // It为vi的迭代器类型vector<long>::iterator T为long类型
    Blob<long> a2(vi.begin(), vi.end());
    //实例化Blob<string>以及list<const char *>::iterator参数
    Blob<string> a3(w.begin(), w.end());
}

std::string getClearName(const char *name)
{
    int status = -1;
    char *clear_name = abi::__cxa_demangle(name, NULL, NULL, &status);
    const char *demangle_name = (status == 0) ? clear_name : name;
    std::string ret_val(demangle_name);
    free(clear_name);
    return ret_val;
}
void use_tempmove()
{
    int i = 100;
    cout << "my_move(i) type is " << getClearName(typeid(my_move(i)).name()) << endl;
    //推断规则
    /*
    1  T被推断为int &
    2  remove_reference<int &>的type成员是int
    3  my_move 的返回类型是int&&
    4  推断t类型为int& && 通过折叠规则t为int&类型
    5  最后这个表达式变为 int && my_move(int &t)
    */

    auto rb = my_move(43);
    cout << "my_move(43) type is " << getClearName(typeid(my_move(i)).name()) << endl;
    //推断规则
    /*
    1  T被推断为int
    2  remove_reference<int>的type成员是int
    3  my_move 的返回类型为int&&
    4  my_move 的参数t类型为int &&
    5  最后这个表达式变为 int && my_move(int && t)
    */
}

// template <typename F, typename T1, typename T2>
// void flip1(F f, T1 t1, T2 t2)
// {
//     f(t2, t1);
// }

void ftemp(int v1, int &v2)
{
    cout << v1 << " " << ++v2 << endl;
}

void gtemp(int &&i, int &j)
{
    cout << "i is " << i << " j is " << j << endl;
}

void use_ftemp()
{
    int j = 100;
    int i = 99;
    ftemp(42, i);
    flip1(ftemp, j, 42);
    cout << "i is " << i << " j is " << j << endl;
    //模板为T1&&类型，当传递int值给flip2时，T变为int&
    //通过折叠t1与t2变为int&类型,实现了绑定外部实参的效果
    flip2(ftemp, j, 42);
    cout << "i is " << i << " j is " << j << endl;

    // flip2(gtemp, j, 42) 会报错
    // 因为42作为右值纯递给flip2，t2会被折叠为int类型
    // t2传递给gtemp第一个参数时，int&&无法绑定int类型

    flip(gtemp, i, 42);
    cout << "i is " << i << " j is " << j << endl;
}

void use_printtemp()
{
    int i = 100;
    string s = "hello zack!!!";
    print(cout, i, s, 42);
}

void test_strvectmp()
{
    auto strVec = StrVecTemp<string>();
    strVec.push_back("hello zack");
    StrVecTemp<string> strVec2(strVec);
    strVec2.push_back("hello rolin");
    StrVecTemp<string> strVec3 = strVec;
    for_each(strVec.begin(), strVec.end(), [](auto data)
             { cout << data << " "; });
    cout << endl;

    for_each(strVec2.begin(), strVec2.end(), [](auto data)
             { cout << data << " "; });
    cout << endl;

    strVec3.emplace_back(10, 'b');
    for_each(strVec3.begin(), strVec3.end(), [](auto data)
             { cout << data << " "; });
    cout << endl;
}

//特例化
template <>
int compare(const char *const &p1, const char *const &p2)
{
    cout << "use compare<> const char * const " << endl;
    return strcmp(p1, p2);
}

void testcompare()
{
    const char *p1 = "h1";
    const char *p2 = "mom";
    //调用特例化版本
    compare(p1, p2);
    //调用第二个版本
    compare("hi", "mom");
}