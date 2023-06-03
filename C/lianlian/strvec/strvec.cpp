#include"strvec.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
std::allocator<std::string> StrVec::alloc;
void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
//重新开辟空间
void StrVec::reallocate()
{
    string *newdata = nullptr;
    //数组为空的情况
    if (elements == nullptr || cap == nullptr || first_free == nullptr)
    {
        newdata = alloc.allocate(1);
        // elements和first_free都指向首元素
        elements = newdata;
        first_free = newdata;
        // cap指向数组尾元素的下一个位置。
        cap = newdata + 1;
        return;
    }
    //不为空则扩充两倍空间
    newdata = alloc.allocate(size() * 2);
    //新内存空闲位置
    auto dest = newdata;
    //旧内存有效位置
    auto src = elements;
    //通过移动操作将旧数据放到新内存中
    for (size_t i = 0; i != size(); ++i)
    {
        alloc.construct(dest++, std::move(*src++));
    }
    //移动后旧内存数据无效，一定要删除
    free();
    //更新数据位置
    elements = newdata;
    //更新第一个空闲位置
    first_free = dest;
    //更新容量
    cap = elements + size() * 2;
}

//释放操作
void StrVec::free()
{
    //判断elements是否为空
    if (elements == nullptr)
    {
        return;
    }

    auto dest = elements;
    //要先遍历析构每一个对象
    for (size_t i = 0; i < size(); i++)
    {
        // destroy会调用每一个元素的析构函数
        alloc.destroy(dest++);
    }
    //再整体回收内存
    alloc.deallocate(elements, cap - elements);
    elements = nullptr;
    cap = nullptr;
    first_free = nullptr;
}

// copy指定范围的元素到新的内存中,返回新元素的地址和第一个空闲元素地址的pair
std::pair<std::string *, std::string *> StrVec::alloc_n_copy(
    const std::string *b, const std::string *e)
{
    auto newdata = alloc.allocate(e - b);
    //将原数据用来初始化新空间
    auto first_free = uninitialized_copy(b, e, newdata);
    return {newdata, first_free};
}

//拷贝构造函数
StrVec::StrVec(const StrVec &strtmp)
{
    //将形参数据拷贝给自己
    auto rsp = alloc_n_copy(strtmp.begin(), strtmp.end());
    //更新elements, cap，first_free
    elements = rsp.first;
    first_free = rsp.second;
    cap = rsp.second;
}

//拷贝赋值运算符
StrVec &StrVec::operator=(const StrVec &strtmp)
{
    cout << "this is copy operator = " << endl;
    //防止自赋值
    if (this == &strtmp)
    {
        return *this;
    }
    //将形参数据拷贝给自己
    auto rsp = alloc_n_copy(strtmp.begin(), strtmp.end());
    //更新elements, cap，first_free
    elements = rsp.first;
    first_free = rsp.second;
    cap = rsp.second;
}
//析构
StrVec::~StrVec()
{
    free();
}

//抛出元素
void StrVec::pop_back(std::string &s)
{
    if (first_free == nullptr)
    {
        return;
    }

    if (size() == 1)
    {
        s = *elements;
        alloc.destroy(elements);
        first_free = nullptr;
        elements = nullptr;
        return;
    }

    s = *(--first_free);
    alloc.destroy(first_free);
}

//移动赋值运算符
StrVec &StrVec::operator=(StrVec &&src)
{
    cout << "this is move operator = " << endl;
    if (this != &src)
    {
        //释放自己的空间操作
        this->free();
        //接管源对象资源
        this->elements = src.elements;
        this->first_free = src.first_free;
        this->cap = src.cap;
        //将源对象成员赋值为空
        src.elements = src.first_free = src.cap = nullptr;
    }

    return *this;
}
