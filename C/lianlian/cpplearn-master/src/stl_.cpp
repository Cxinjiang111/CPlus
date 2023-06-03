#include "../inc/stl_.h"
#include "../inc/class_.h"
#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <forward_list>
#include <stack>
#include <queue>

using namespace std;
void use_stl()
{
    // 保存double数据的deque
    deque<double> dd;
    // vector里存储了vector<string>
    vector<vector<string>> strvec_vec;
    //通过begin和end访问容器元素
    for (auto begin = dd.begin(); begin != dd.end(); begin++)
    {
        cout << *begin << endl;
    }
    // vector<string>容器的迭代器
    vector<string>::iterator strit;
    // deque<double>容器的迭代器
    deque<double>::iterator ddit;
    //列表初始化
    list<string> persons = {"zack", "rolin", "vivo"};
    vector<char *> articles = {"c++", "althogram", "why"};
    //将一个容器copy给另一个相同类型的容器
    list<string> persons2(persons);
    //通过迭代器实现copy
    list<string> persons3(persons.begin(), persons.end());
    // assign实现数据copy
    persons2.assign(persons.begin(), persons.end());
    //用指定数目和初始值
    persons2.assign(5, "zack");
    //交换两个容器
    vector<string> svec1(10);
    vector<string> svec2(24);
    swap(svec1, svec2);

    // push_back添加尾元素
    vector<string> svec3;
    svec3.push_back("good idea!");
    // push_front添加头部元素
    list<int> nlist;
    for (int i = 0; i < 100; i++)
    {
        nlist.push_front(i);
    }

    // insert 插入
    vector<string> strinvec;
    // vector不支持push_front，可以通过insert实现
    // 在vector头部插入元素会很慢，以为vector要移动所有元素
    strinvec.insert(strinvec.begin(), "zack");
    list<string> strlist;
    //相当于push_back
    strlist.insert(strlist.end(), "zack");
    //批量插入
    strlist.insert(strlist.end(), 10, "ai");

    vector<string> names = {"zack", "rolin", "bob", "pior"};
    //通过迭代器插入
    strlist.insert(strlist.begin(), names.end() - 2, names.end());
    //通过参数列表插入
    strlist.insert(strlist.end(), {"vivo", "hua", "nokia"});

    // sales_data对象的list
    list<Sales_data> sales_list;
    //传递Sales_data的构造函数
    sales_list.emplace_back(string("love easy"), 200, 1.8);

    auto first = sales_list.front();
    auto last = sales_list.back();
    auto strfirst = svec3.front();
    auto strfirst2 = svec3.at(0);
    auto strfrist3 = svec3[0];

    strinvec.push_back("hello");
    //删除尾部元素
    strinvec.pop_back();

    forward_list<string> forlist;
    forlist.push_front("hello");
    //删除头部元素
    forlist.pop_front();
    //删除头部元素
    strinvec.erase(strinvec.begin());
    //范围删除，删除从头部到尾部的元素
    strinvec.erase(strinvec.begin(), strinvec.end());
    //删除所有
    strinvec.clear();

    list<int> numlist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    for (auto iter = numlist.begin(); iter != numlist.end();)
    {
        if (*iter % 2)
        {
            //删除后返回下一个迭代器
            iter = numlist.erase(iter);
        }
        else
        {
            //没删除则移动迭代器
            iter++;
        }
    }

    forward_list<int> numlist2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    // numlist2的首前元素，第一个元素之前的位置，不能解引用，因为该位置没有元素。
    auto prev = numlist2.before_begin();
    //第一个元素
    auto curr = numlist2.begin();
    while (curr != numlist2.end())
    {
        if (*curr % 2)
        {
            //返回删除元素的下一个元素
            curr = numlist2.erase_after(prev);
        }
        else
        {
            // prev更更新为curr
            prev = curr;
            // curr向后移动
            curr++;
        }
    }

    vector<string> strvec2 = {"zack", "lucy", "vivo", "rolin"};
    cout << "strvec2.size is " << strvec2.size() << endl;
    cout << "strvec2.capacity is " << strvec2.capacity() << endl;
    //插入一个元素，导致size变化
    //当size>=capacity是，capacity也会增加
    strvec2.push_back("lirus");
    cout << "strvec2.size is " << strvec2.size() << endl;
    cout << "strvec2.capacity is " << strvec2.capacity() << endl;
    //修改大小
    strvec2.resize(20);
    //修改容量
    strvec2.reserve(23);
    for (auto it = strvec2.begin(); it != strvec2.end(); it++)
    {
        cout << "data is " << *it << endl;
    }

    cout << "strvec2.size is " << strvec2.size() << endl;
    cout << "strvec2.capacity is " << strvec2.capacity() << endl;
    //基于vector构建stack
    stack<string, vector<string>> strstack;
    //基于vector构造priority_queue
    priority_queue<string, vector<string>> strpque;
    //基于list构造一个queue
    queue<list<string>> strqueue;
    //构造一个
    stack<int> intStack;
    for (int i = 0; i < 10; i++)
    {
        intStack.push(i);
    }
    // stack不为空
    while (!intStack.empty())
    {
        //访问栈顶元素但是不取出
        auto data = intStack.top();
        cout << data << endl;
        //栈顶元素出栈
        intStack.pop();
    }
    //队列
    queue<int> numque;
    for (int i = 0; i < 10; i++)
    {
        numque.push(i);
    }

    while (!numque.empty())
    {
        //访问队列首元素
        auto &first = numque.front();
        cout << first << " ";
        //弹出队首元素
        numque.pop();
    }

    cout << endl;
}