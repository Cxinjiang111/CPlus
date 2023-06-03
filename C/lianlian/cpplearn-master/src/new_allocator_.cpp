#include "../inc/new_allocator_.h"
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

int get_size_new()
{
    return 42;
}
void new_array_1()
{
    int *p_array = new int[get_size_new()]();
    for (int i = 0; i < get_size_new(); i++)
    {
        cout << *(p_array + i) << " ";
    }

    delete[] p_array;
    cout << endl;
}

void new_array_2()
{
    //定义数组类型
    typedef int array_type[10];
    //动态开辟数组空间
    int *p_array = new (array_type);
    delete[] p_array;
}

void new_array_3()
{
    //通过{}初始化动态数组
    int *p_array = new int[10]{1, 2, 3, 4};
    //释放动态数组
    delete[] p_array;
}

void new_array()
{
    int n = 0;
    //开辟一个大小为0的数组
    int *p_array = new int[n];
    for (int *p = p_array; p != n + p_array; p++)
    {
        cout << *p << " ";
    }

    delete[] p_array;
}

void unique_array()
{
    //开辟一个20个整形的动态数组，用unique_ptr管理它。
    auto unarray = unique_ptr<int[]>(new int[20]());

    //可以通过下标访问数组元素
    for (size_t i = 0; i < 10; i++)
    {
        unarray[i] = 1024;
    }

    //释放这个动态数组
    unarray.release();
}

void use_shared_array_1()
{
    // 开辟一个5个整形的动态数组，用shared_ptr管理它
    auto sharray = shared_ptr<int[]>(new int[5]{1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++)
    {
        cout << sharray[i] << " ";
    }
    sharray.reset();
    cout << endl;
}

void use_shared_array()
{
    shared_ptr<int> sharray = shared_ptr<int>(new int[5], [](int *p)
                                              { delete[] p; });
    sharray.reset();
}

void use_allocator_1()
{
    allocator<string> alloc;
    // allocator分配5个string类型对象的空间
    // 这些空间未构造
    auto p = alloc.allocate(5);
    auto q = p;
    string str = "c";
    for (; q != p + 5; q++)
    {
        //构造字符串，每次字符串增加c字符
        alloc.construct(q, str);
        str += "c";
    }
    // //打印构造的字符串列表
    for (q = p; q != p + 5; q++)
    {
        cout << *q << endl;
    }

    //销毁开辟的空间
    alloc.deallocate(p, 5);
}

void use_allocator()
{
    vector<int> ivec = {1, 2, 3, 4, 5};
    allocator<int> alloc;
    //开辟2倍ivec大小的空间
    auto p = alloc.allocate(ivec.size() * 2);
    //将ivec的内容copy至alloc开辟的空间里
    //返回q指向剩余未构造的内存空间的起始地址
    auto q = uninitialized_copy(ivec.begin(), ivec.end(), p);
    //将剩余元素初始化为42
    uninitialized_fill_n(q, ivec.size(), 42);
}