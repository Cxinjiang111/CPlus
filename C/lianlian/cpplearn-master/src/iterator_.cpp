#include "../inc/iterator_.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
void iterator_func()
{
    string s("some string");
    if (s.begin() != s.end())
    {
        auto it = s.begin();
        *it = toupper(*it);
    }

    for (auto iter = s.begin(); iter != s.end() && !isspace(*iter); iter++)
    {
        *iter = toupper(*iter);
    }

    cout << "str is " << s << endl;

    // it能读写vector<int>的元素
    vector<int>::iterator it;
    // it2能读写string对象中的字符
    vector<string>::iterator it2;
    // it3 只能读元素,不能写元素
    vector<int>::const_iterator it3;
    // it4 只能读字符，不能写字符
    vector<string>::const_iterator it4;

    vector<int> v;
    const vector<int> cv;
    // vit1的类型是vector<int>::iterator
    auto vit1 = v.begin();
    // vit2的类型是vector<int>::const_iterator
    auto vit2 = cv.begin();
    //通过cbegin和cend可以获取常量迭代器
    // cvit 类型为vector<int>::const_iterator
    auto cvit = v.cbegin();

    vector<string> text = {
        "zack",
        "vivo",
        "",
        "lisus",
        "lidaguo",
        "liuww",
        "lilian",
        "db",
        "jack",
        "mongo",
    };
    for (auto it = text.begin(); it != text.end() && !it->empty(); ++it)
    {
        cout << *it << endl;
    }

    auto itdel = text.begin();
    while (itdel != text.end())
    {
        if (itdel->empty())
        {
            itdel = text.erase(itdel);
            continue;
        }
        itdel++;
    }

    for (auto it = text.begin(); it != text.end(); ++it)
    {
        cout << *it << endl;
    }

    vector<int> orderv = {1,
                          2,
                          3,
                          5,
                          6,
                          8,
                          9,
                          10};
    bool bfind = false;
    auto findit = orderv.begin();
    auto beginit = orderv.begin();
    auto endit = orderv.end();

    while (beginit != endit)
    {
        auto midit = beginit + (endit - beginit) / 2;
        if (*midit == 9)
        {
            findit = midit;
            bfind = true;
            break;
        }

        if (*midit > 9)
        {
            endit = midit - 1;
        }

        if (*midit < 9)
        {
            beginit = midit + 1;
        }
    }

    if (bfind)
    {
        cout << "find success, iter val is " << *findit << endl;
    }
}