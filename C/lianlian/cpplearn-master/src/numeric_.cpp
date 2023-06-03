#include "../inc/numeric_.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
using namespace std;
using namespace std::placeholders;
void use_numeric()
{
    vector<int> nvec = {1, 2, 3, 4, 5, 6, 7};
    //调用accumulate累加，sum的初始值为0，累加结果写入sum
    auto sum = accumulate(nvec.begin(), nvec.end(), 0);
    cout << "sum is " << sum << endl;
    list<string> strlist = {"hello", "zack", "good", "idea"};
    string stradd = accumulate(strlist.begin(), strlist.end(), string(""));
    cout << "str add result is " << stradd << endl;
    list<string> strlist2 = {"hello", "zack", "good", "idea"};
    bool bequa = equal(strlist.begin(), strlist.end(), strlist2.begin());
    if (bequa)
    {
        cout << "strlist is equal to strlist2" << endl;
    }
    else
    {
        cout << "strlist is not equal to strlist2" << endl;
    }

    vector<int> nvec2 = {1, 2, 3, 4};
    //将nvec2中所有元素设置为0
    fill(nvec2.begin(), nvec2.end(), 0);
    //将nvec2中前半部分设置为10
    fill(nvec2.begin(), nvec2.begin() + nvec2.size() / 2, 10);
    vector<int> vec;
    fill_n(vec.begin(), vec.size(), 0);

    //空vector
    vector<int> nvec4;
    // back_inserter绑定nvec4并返回迭代器
    auto iter = back_inserter(nvec4);
    //对迭代器的赋值就是对nvec插入元素
    *iter = 2;
    *iter = 4;
    for (auto it = nvec4.begin(); it != nvec4.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    //空vector
    vector<int> nvec5;
    // back_inserter绑定nvec5并返回迭代器
    auto iter5 = back_inserter(nvec5);
    fill_n(iter5, 10, 0);

    int a1[] = {0, 1, 2, 3, 4, 5, 6};
    constexpr int nszie = sizeof(a1) / sizeof(int);
    int a2[nszie];
    //将a1内容copy到a2中
    copy(begin(a1), end(a1), a2);

    vector<int> nvec6 = {1, 2, 3, 4};
    //将nvec6中所有元素为3的设置为32
    replace(nvec6.begin(), nvec6.end(), 3, 32);

    //原始数据列表
    list<int> ilist = {0, 1, 2, 3, 4, 5};
    //空向量
    vector<int> rcpvec;
    //将ilist中的数据copy到rcpvec里，但是将其中的0替换为42
    replace_copy(ilist.begin(), ilist.end(), back_inserter(rcpvec), 0, 42);
}

void erase_dup(vector<string> &words)
{
    //先将words中的词语排序
    sort(words.begin(), words.end());
    // unique会移动元素，将不重复的元素放在前边，重复的放在后边
    // unique返回不重复的最后一个元素的位置
    const auto uniqueiter = unique(words.begin(), words.end());
    //调用erase将重复的元素删除
    words.erase(uniqueiter, words.end());

    // for (auto it = words.begin(); it != words.end(); it++)
    // {
    //     cout << *it << " ";
    // }
    // cout << endl;
}

bool isShort(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void use_predicate()
{
    vector<string> words = {"hello", "za", "zack", "no matter", "what"};
    sort(words.begin(), words.end(), isShort);
    for (auto it = words.begin(); it != words.end(); it++)
    {
        cout << *it << endl;
    }
}

void use_lambda()
{
    auto f = []()
    { return 42; };
    cout << " f is " << f() << endl;

    [](const string &s1, const string &s2) -> bool
    { return s1.size() < s2.size(); };
    vector<string> words = {"hello", "za", "zack", "no matter", "what"};
    stable_sort(words.begin(), words.end(), [](const string &s1, const string &s2) -> bool
                { return s1.size() < s2.size(); });
    for (auto it = words.begin(); it != words.end(); it++)
    {
        cout << *it << endl;
    }
}

int use_bigger(int sz)
{
    vector<string> words = {"hello", "za", "zack", "no matter", "what"};
    //先排序去除重复单词
    erase_dup(words);
    //再稳定排序，按照长度有小到大
    stable_sort(words.begin(), words.end(), [](const string &s1, const string &s2) -> bool
                { return s1.size() < s2.size(); });
    auto findit = find_if(words.begin(), words.end(), [sz](const string &s)
                          { return s.size() > sz; });
    for_each(findit, words.end(), [](const string &s)
             { cout << s << " "; });
    cout << endl;
    return words.end() - findit;
}

void lambda_catch()
{
    int val = 10;
    auto fn = [val]
    { return val; };
    val = 200;
    auto fv = fn();
    cout << "fv is " << fv << endl;
}

void lambda_catch_r()
{
    int val = 10;
    auto fn = [&val]
    { return val; };
    val = 200;
    auto fv = fn();
    cout << "fv is " << fv << endl;
}

int use_bigger2(ostream &os, char c, int sz)
{
    vector<string> words = {"hello", "za", "zack", "no matter", "what"};
    //先排序去除重复单词
    erase_dup(words);
    //再稳定排序，按照长度有小到大
    stable_sort(words.begin(), words.end(), [](const string &s1, const string &s2) -> bool
                { return s1.size() < s2.size(); });
    auto findit = find_if(words.begin(), words.end(), [sz](const string &s)
                          { return s.size() > sz; });
    // os 按照引用方式捕获，其余变量c 通过= 值方式隐士捕获。
    for_each(findit, words.end(), [=, &os](const string &s)
             { os << s << c; });

    // c 按照值的方式捕获，其余按照引用方式捕获。
    for_each(findit, words.end(), [&, c](const string &s)
             { os << s << c; });
    cout << endl;
    return words.end() - findit;
}

void mutalble_lam()
{
    int val = 100;
    auto fn = [val]() mutable
    {
        return ++val;
    };

    cout << "val is " << val << endl;

    cout << "fn val is " << fn() << endl;

    val = 200;
    cout << "val is " << val << endl;

    cout << "fn val is " << fn() << endl;
}

void rt_lambda()
{
    vector<int> nums = {-1, 2, 3, -5, 6, 7, -9};
    transform(nums.begin(), nums.end(), nums.begin(), [](int a)
              { return a < 0 ? -a : a; });
    for_each(nums.begin(), nums.end(), [](int a)
             { cout << a << endl; });

    transform(nums.begin(), nums.end(), nums.begin(), [](int a) -> int
              { if (a < 0)  return -a; else return a; });
}

bool check_size(const string &str, int sz)
{
    if (str.size() > sz)
    {
        return true;
    }

    return false;
}

void calsize_count()
{
    string str = "hello";
    //将check_size第一个参数绑定给bind_check
    auto bind_check = bind(check_size, _1, 6);
    //相当于调用check_size(str,6)
    bool bck = bind_check(str);
    if (bck)
    {
        cout << "check res is true" << endl;
    }
    else
    {
        cout << "check res is false" << endl;
    }
}

int use_bigger3(ostream &os, char c, int sz)
{
    vector<string> words = {"hello", "za", "zack", "no matter", "what"};
    //先排序去除重复单词
    erase_dup(words);
    //再稳定排序，按照长度有小到大
    stable_sort(words.begin(), words.end(), [](const string &s1, const string &s2) -> bool
                { return s1.size() < s2.size(); });
    auto findit = find_if(words.begin(), words.end(), bind(check_size, _1, sz));

    // c 按照值的方式捕获，其余按照引用方式捕获。
    for_each(findit, words.end(), [&, c](const string &s)
             { os << s << c; });
    cout << endl;
    return words.end() - findit;
}