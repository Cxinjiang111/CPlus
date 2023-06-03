#include "../inc/map_.h"
#include <map>
#include <string>
#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <unordered_map>
using namespace std;

void use_map()
{
    map<string, size_t> word_count;
    string word;
    while (cin >> word)
    {
        word_count[word]++;
    }

    for (const auto &val : word_count)
    {
        cout << "word is " << val.first << " counts are " << val.second << endl;
    }
}

void use_set()
{
    map<string, size_t> word_count;
    set<string> excludes = {"zack", "joyce", "mongo"};
    string word;
    while (cin >> word)
    {
        if (excludes.find(word) == excludes.end())
        {
            word_count[word]++;
        }
    }

    for (const auto &val : word_count)
    {
        cout << "word is " << val.first << " counts are " << val.second << endl;
    }
}

void use_multiset()
{
    vector<int> ivec;
    for (int i = 0; i < 10; i++)
    {
        ivec.push_back(i);
        //数据重复插入一次
        ivec.push_back(i);
    }

    set<int> iset(ivec.begin(), ivec.end());
    multiset<int> imulset(ivec.begin(), ivec.end());
    for_each(iset.begin(), iset.end(), [](const int &i)
             { cout << i << " "; });
    cout << endl;

    for_each(imulset.begin(), imulset.end(), [](const int &i)
             { cout << i << " "; });
    cout << endl;
}

bool compareIsbn(const BookData &b1, const BookData &b2)
{
    return b1.isbn < b2.isbn;
}

void use_defkey()
{
    multiset<BookData, decltype(compareIsbn) *> bookmap(compareIsbn);
}

void use_pair()
{
    //可以定义多种类型的pair
    pair<string, string> str_pair;
    pair<string, vector<int>> vec_pair;
    // pair的初始化
    //用{}初始化
    pair<string, string> author = {"zack", "fair"};
    //用make_pair初始化
    auto mkpair = make_pair("zack", 1);
    //用pair模板生成pair对象
    auto pairinit = pair<string, size_t>("zack", 1024);
    //用map的value_type
    auto vtypepair = map<string, size_t>::value_type("zack", 1023);
}

void map_iter()
{
    map<string, size_t> word_count;
    word_count["zack"] = 1024;
    auto mapit = word_count.begin();
    //*mapit是指向一个<const string, size_t>pair对象的引用
    //打印第一个元素的key值
    cout << mapit->first << endl;
    //打印第一个元素的value值
    cout << mapit->second << endl;
    //不允许修改key值，因为key值为const不允许修改
    // mapit->first = "rolin";
    //可以修改value值
    mapit->second = 222;
}

void set_iter()
{
    set<int> iset = {1, 3, 5, 7, 9, 0, 2, 4, 6, 11};
    for (auto it = iset.begin(); it != iset.end(); it++)
    {
        //解引用获得key，key无法修改
        //(*it)++;
        cout << *it << " ";
    }
}

void map_iteration()
{
    map<string, size_t> word_count;
    word_count["zack"] = 1;
    word_count["vivo"] = 2;
    word_count["fair"] = 3;
    for (auto it = word_count.begin(); it != word_count.end(); it++)
    {
        cout << "key is " << it->first << " ,value is " << it->second << endl;
    }
}

void insert_set()
{
    set<int> iset;
    vector<int> ivec = {1, 3, 5, 7, 9, 1, 3, 5, 7, 9};
    iset.insert(ivec.begin(), ivec.end());
    // iset内容为1, 3, 5, 7, 9
    for_each(iset.begin(), iset.end(), [](const int &i)
             { cout << i << " "; });
    iset.insert({2, 4, 6, 8, 10, 2, 4, 6, 8, 10});
    // iset内容为1,2,3,4,5,6,7,8,9,10
    for_each(iset.begin(), iset.end(), [](const int &i)
             { cout << i << " "; });
}

void insert_map()
{
    map<string, size_t> word_count;
    //通过make_pair插入
    word_count.insert(make_pair("zack", 1024));
    //通过{}插入
    word_count.insert({"rolin", 1234});
    //通过pair构造出入
    word_count.insert(pair<string, size_t>("lucas", 112));
    //通过map::value_type插入
    word_count.insert(map<string, size_t>::value_type("Lily", 2333));

    auto res = word_count.insert(make_pair("zack", 2234));
    // insert返回一个pair，pair的first是指向给定key的迭代器
    // pair的second返回的是bool值，如果给定的key已经存在，bool值为false
    if (!res.second)
    {
        cout << res.first->first << " has been inserted into map" << endl;
    }

    auto delres = word_count.erase("zack");
    if (delres)
    {
        cout << "del zack success, res is " << delres << endl;
    }
    else
    {
        cout << "zack is not in map" << endl;
    }
}

void find_map()
{
    map<string, size_t> word_count;
    auto findit = word_count.find("zack");
    if (findit != word_count.end())
    {
        cout << "find key is " << findit->first << "value is " << findit->second << endl;
    }
    else
    {
        cout << "key zack not found" << endl;
    }

    // authors为multimap允许key重复
    multimap<string, string> authors;
    authors.insert(make_pair("zack", "i see i know"));
    authors.insert(make_pair("zack", "who am i"));
    //对于map遍历，lambda表达式要用pair做参数
    for_each(authors.begin(), authors.end(), [](pair<string, string> a)
             { cout << a.first << " " << a.second << endl; });
    //返回包含zack的元素个数
    auto count = authors.count(string("zack"));
    //查找第一个zack出现的迭代器
    auto auit = authors.find(string("zack"));
    while (count > 0)
    {
        cout << auit->second << endl;
        auit++;
        count--;
    }

    for (auto lowit = authors.lower_bound("zack"); lowit != authors.upper_bound("zack"); lowit++)
    {
        cout << "key is " << lowit->first << " val is " << lowit->second << endl;
    }

    auto equal_range = authors.equal_range("zack");
    for (; equal_range.first != equal_range.second; equal_range.first++)
    {
        cout << "key is " << equal_range.first->first << " val is " << equal_range.first->second << endl;
    }
}

void use_unorderd_map()
{
    unordered_map<string, size_t> word_count;
    string word;
    while (cin >> word)
    {
        word_count[word]++;
    }

    for (const auto &word : word_count)
    {
        cout << "key is " << word.first << " value is " << word.second << endl;
    }
}