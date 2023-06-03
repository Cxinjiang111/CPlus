#include "../inc/stl_iter_.h"
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
using namespace std;
void use_inserter()
{
    list<int> list1 = {1, 2, 3, 4};
    list<int> list2, list3, list4;
    copy(list1.begin(), list1.end(), front_inserter(list2));
    copy(list1.begin(), list1.end(), back_inserter(list3));
    copy(list1.begin(), list1.end(), inserter(list4, list4.begin()));

    for_each(list2.begin(), list2.end(), [](const int &i)
             { cout << i << " "; });
    cout << endl;

    for_each(list3.begin(), list3.end(), [](const int &i)
             { cout << i << " "; });
    cout << endl;

    for_each(list4.begin(), list4.end(), [](const int &i)
             { cout << i << " "; });
    cout << endl;
}

void use_istreamiter()
{
    //输入流迭代器
    istream_iterator<int> in_int(cin);
    //迭代器终止标记
    istream_iterator<int> in_eof;
    vector<int> in_vec;
    while (in_int != in_eof)
    {
        in_vec.push_back(*in_int++);
    }
    for_each(in_vec.begin(), in_vec.end(), [](const int &i)
             { cout << i << " "; });
    cout << endl;
}

void use_ostreamiter()
{
    vector<int> in_vec = {1, 3, 4, 2, 5, 6, 7, 9};
    ostream_iterator<int> out_in(cout, " ");
    for (auto data : in_vec)
    {
        *out_in++ = data;
    }
    cout << endl;
}

void use_reverseiter()
{
    vector<int> in_vec = {1, 3, 4, 2, 5, 6, 7, 9};
    for (auto rit = in_vec.crbegin(); rit != in_vec.crend(); rit++)
    {
        cout << *rit << " ";
    }
    cout << endl;

    string line = "FIRST,SECOND,LAST";
    auto rcomma = find(line.crbegin(), line.crend(), ',');
    //反向迭代器获取数据是反向的
    cout << string(line.crbegin(), rcomma) << endl;
    //通过base将反向迭代器转化为正向的
    cout << string(rcomma.base(), line.cend()) << endl;
}