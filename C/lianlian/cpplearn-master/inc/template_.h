#ifndef __template_h__
#define __template_h__
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <memory>
#include <type_traits>
#include <utility>
#include <queue>
using namespace std;
template <typename T>
int compare(const T &v1, const T &v2)
{
    cout << "use compare T&" << endl;
    if (v1 < v2)
        return -1;
    if (v2 < v1)
        return 1;
    return 0;
}

//带字面常量的比较函数
template <size_t N, size_t M>
int compare(const char (&a1)[N], const char (&a2)[M])
{
    cout << "use const char (&)[N]" << endl;
    strcmp(a1, a2);
}

extern void testcompare();

template <typename T, typename U>
int printData(const T &t, const U &u)
{
    cout << "t is " << t << endl;
    cout << "u is " << u << endl;
}

extern void use_template();

template <unsigned N, unsigned M>
int compareArray(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

template <typename>
class BlobPtr;

template <typename>
class Blob;

template <typename T>
bool operator==(const Blob<T> &, const Blob<T> &);
//定义模板类型的blob
template <typename T>
class Blob
{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // T类型的BlobPtr是T类型的Blob的友元类
    friend class BlobPtr<T>;
    //重载==运算符
    friend bool operator==(const Blob<T> &, const Blob<T> &);
    //构造函数
    Blob()
    {
        data = make_shared<std::vector<T>>();
    }
    Blob(std::initializer_list<T> il)
    {
        data = make_shared<std::vector<T>>(il);
        // for (const T &m : il)
        // {
        //     data->push_back(m);
        // }
    }

    template <typename It>
    Blob(It b, It e);
    // Blob 中元素数目
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    //添加和删除元素
    void push_back(const T &t) { data->push_back(t); }
    //移动版本的push_back
    void push_back(const T &&t) { data->push_back(std::move(t)); }
    //删除元素
    void pop_back();
    //元素访问
    T &back();
    T &operator[](size_type i);

private:
    std::shared_ptr<std::vector<T>> data;
    //校验数据是否有效
    void check(size_type i, const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
void Blob<T>::pop_back()
{
    if (data->empty())
    {
        return;
    }
    data->pop_back();
}

template <typename T>
T &Blob<T>::back()
{
    return data->back();
}

template <typename T>
T &Blob<T>::operator[](size_type i)
{
    check(i, "index out of range");
    return (*data)[i];
}

template <typename T>
bool operator==(const Blob<T> &b1, const Blob<T> &b2)
{
    if (b1.size() > b2.size())
    {
        return true;
    }

    if (b1.siz() < b2.size())
    {
        return false;
    }

    for (unsigned int i = 0; i < b1.size(); i++)
    {
        if (b1.data[i] == b2.data[i])
        {
            continue;
        }

        return b1.data[i] > b2.data[i];
    }

    return true;
}

//与模板类的普通成员不同，成员模板是函数模板
//模板类的T类型
template <typename T>
//成员函数模板It类型
template <typename It>
Blob<T>::Blob(It b, It e)
{
    //通过迭代器构造
    data = std::make_shared<std::vector<T>>(b, e);
}
extern void use_tempmemfunc();
template <typename T>
class BlobPtr
{
public:
    BlobPtr() : curr(0) {}
    BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    //递增和递减
    BlobPtr &operator++(); //前置运算符
                           // BlobPtr &operator--(); //前置运算符--

    BlobPtr &operator++(int);

private:
    std::shared_ptr<std::vector<T>>
    check(std::size_t, const std::string &) const;
    std::size_t curr; //数组中的当前位置
    //保存一个weak_ptr， 表示底层vector可能被销毁
    std::weak_ptr<std::vector<T>> wptr;
};

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++()
{
    this->curr++;
    return *this;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++(int)
{
    BlobPtr &rt = *this;
    this->curr++;
    return rt;
}
template <typename T>
class Pal
{
};

template <typename T>
class Pal2
{
};

class C
{
    // Pal<C>是C类的友元
    friend class Pal<C>;
    //所有类型的Pal2的类都是C的友元
    template <typename T>
    friend class Pal2;
};

// c2本身是一个模板类
template <typename T>
class C2
{
    //和C2同类型的Pal是C2的所有实例友元
    friend class Pal<T>;
    // Pal2的所有实例都是C2的所有实例友元
    template <typename X>
    friend class Pal2;
    // Pal3是一个普通类，他是C2的所有实例的友元
    friend class Pal3;
};

extern void
use_classtemp();

template <typename Type>
class Bar
{
    //将访问权限授予用来实例化Bar的类型
    friend Type;
};

//定义模板类别名
typedef long long INT64;
//我们可以为实例好的模板类定义别名
typedef Bar<int> mytype;
// C11 可以为模板类定义别名
template <typename T>
using twin = pair<T, T>;
// authors 是一个pair<string, string>
// twin<string> authors;
// infos 是一个pair<int, int>类型
// twin<int> infos;
template <typename T>
using partNo = pair<T, unsigned>;
// books是pair<string, unsigned>类型
// partNo<string> books;
//类模板的static成员
template <typename T>
class Foo
{
public:
    static std::size_t count() { return ctr; }

private:
    static std::size_t ctr;
};

template <typename T>
size_t Foo<T>::ctr = 0;
// size_type是一个类型
// string::size_type;

// 默认情况下，C++语言假定通过作用域运算符访问的名字不是类型。
// 因此，如果我们希望使用一个模板类型参数的类型成员，就必须显式告诉编译器该名字是一个类型。
// 我们通过使用关键字typename来实现这一点：

// 用typename 告知编译器T::value_type是一个类型
template <typename T>
typename T::value_type top(const T &c)
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}

//函数对象，给指定类型的指针执行析构
class DebugDelete
{
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}
    //我们定义一个仿函数，参数是T*类型
    template <typename T>
    void operator()(T *p) const
    {
        os << "deleting unique_str" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};
extern void use_debugdel();
//推断返回类型，通过尾置返回允许我们在参数列表之后的声明返回类型
template <typename It>
auto fcnrf(It beg, It end) -> decltype(*beg)
{
    //处理序列
    //返回迭代器beg指向的元素的引用
    return *beg;
}

// remove_reference 是一个模板
// remove_reference<decltype(*beg)>::type
// type的类型就是beg指向元素的类型
// remove_reference<int&>::type type就是int
// remove_reference<string&>::type type就是string

template <typename It>
auto fcncp(It beg, It end) -> remove_reference<decltype(*beg)>
{
    //返回迭代器beg指向元素的copy
    return *beg;
}

//接受左值引用的模板函数
template <typename T>
void f1(T &t)
{
}

//接受右值引用的模板函数
template <typename T>
void f2(T &&t)
{
}

// f2(42) T就被推断为int
// int i = 100; f2(i) T就被推断为int& 参数类型就变为int& &&
// 当模板函数的参数是一个T类型的右值引用
// 1 传递给该参数的实参是一个右值时，T就是该右值类型
// 2 传递给该参数的实参是一个左值时，T就是该左值引用类型

//折叠规则
// X&& 、X&&& 都会被折叠为X&
// X&& && 会被折叠为X&&
// move 源码
template <typename T>
typename remove_reference<T>::type &&my_move(T &&t)
{
    return static_cast<typename remove_reference<T>::type &&>(t);
}

extern void use_tempmove();

template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2)
{
    f(t2, t1);
}

template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
    f(t2, t1);
}

template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

//当我们传递给flip(f, int, int)时
// T1 变为int &, T2就会变为int &
// std::forward<int&>(t2) ===> t2是int&类型

//当我们传递给flip(f, 42, 100)
// T1 和T2 都是 int
// t1 和t2就是右值引用
// forward<int&&>(t2) ==> t2是int&&类型
extern void ftemp(int v1, int &v2);

extern void use_ftemp();

//可变参数的函数模板
template <typename T>
ostream &print(ostream &os, const T &t)
{
    return os << t; //输出最后一个元素
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args &...rest)
{
    os << t << ", ";
    return print(os, rest...);
}

extern void use_printtemp();

template <typename T>
class StrVecTemp
{
public:
    StrVecTemp() : elements(nullptr), first_free(nullptr),
                   cap(nullptr) {}
    //拷贝构造函数
    StrVecTemp(const StrVecTemp &);
    //拷贝赋值运算符
    StrVecTemp &operator=(const StrVecTemp &);
    //移动构造函数
    StrVecTemp(StrVecTemp &&src) noexcept : elements(src.elements),
                                            first_free(src.first_free), cap(src.cap)
    {
        //将源数据置空
        src.elements = src.first_free = src.cap = nullptr;
    }

    template <class... Args>
    void emplace_back(Args &&...args);

    //析构函数
    ~StrVecTemp();
    //拷贝元素
    void push_back(const T &);
    //抛出元素
    void pop_back(T &s);
    //返回元素个数
    size_t size() const { return first_free - elements; }
    //返回capacity返回容量
    size_t capacity() const { return cap - elements; }
    //返回首元素的指针
    T *begin() const
    {
        return elements;
    }

    //返回第一个空闲元素指针
    T *end() const
    {
        return first_free;
    }

private:
    //判断容量不足靠皮新空间
    void chk_n_alloc()
    {
        if (size() == capacity())
        {
            reallocate();
        }
    }

    //重新开辟空间
    void reallocate();
    // copy指定范围的元素到新的内存中
    std::pair<T *, T *> alloc_n_copy(const T *, const T *);
    //释放空间
    void free();
    //数组首元素的指针
    T *elements;
    //指向数组第一个空闲元素的指针
    T *first_free;
    //指向数组尾后位置的指针
    T *cap;
    //初始化alloc用来分配空间
    static std::allocator<T> alloc;
};
template <typename T>
std::allocator<T> StrVecTemp<T>::alloc;

//实现区间copy
template <typename T>
std::pair<T *, T *> StrVecTemp<T>::alloc_n_copy(const T *b, const T *e)
{
    auto newdata = alloc.allocate(e - b);
    //用来的数据初始化新的空间
    auto first_free = uninitialized_copy(b, e, newdata);
    return {newdata, first_free};
}

//实现拷贝构造函数
template <class T>
StrVecTemp<T>::StrVecTemp(const StrVecTemp &strVec)
{
    auto rsp = alloc_n_copy(strVec.begin(), strVec.end());
    //利用pair类型更新elements, cap, first_free
    elements = rsp.first;
    first_free = rsp.second;
    cap = rsp.second;
}

//拷贝赋值运算符
template <class T>
StrVecTemp<T> &StrVecTemp<T>::operator=(const StrVecTemp &strVec)
{
    if (this == &strVec)
    {
        return *this;
    }
    //如果不是自赋值，就将形参copy给自己
    auto rsp = alloc_n_copy(strVec.begin(), strVec.end());
    elements = rsp.first;
    first_free = rsp.second;
    cap = rsp.second;
}

//析构函数
template <class T>
StrVecTemp<T>::~StrVecTemp()
{
    //判断elements是否为空
    if (elements == nullptr)
    {
        return;
    }
    //缓存第一个有效元素的地址
    auto dest = elements;
    //循环析构
    for (size_t i = 0; i < size(); i++)
    {
        //析构每一个元素
        alloc.destroy(dest++);
    }
    //再回收内存
    alloc.deallocate(elements, cap - elements);
    elements = nullptr;
    cap = nullptr;
    first_free = nullptr;
}

template <class T>
void StrVecTemp<T>::reallocate()
{
    T *newdata = nullptr;
    //数组为空的情况
    if (elements == nullptr || cap == nullptr || first_free == nullptr)
    {
        newdata = alloc.allocate(1);
        elements = newdata;
        first_free = newdata;
        // cap指向数组尾元素的下一个位置
        cap = newdata + 1;
        return;
    }

    //原数据不为空，则扩充size两倍大小
    newdata = alloc.allocate(size() * 2);
    //新内存空闲位置
    auto dest = newdata;
    //就内存的有效位置
    auto src = elements;
    //通过移动操作将旧数据放到新内存中
    for (size_t i = 0; i != size(); ++i)
    {
        alloc.construct(dest++, std::move(*src++));
    }
    //移动完旧数据后一定要删除
    free();
    //更新数据位置
    elements = newdata;
    first_free = dest;
    cap = newdata + size() * 2;
}

//拷贝元素
template <class T>
void StrVecTemp<T>::push_back(const T &t)
{
    chk_n_alloc();
    alloc.construct(first_free++, t);
}
//抛出元素
template <class T>
void StrVecTemp<T>::pop_back(T &s)
{
    //先判断是否为空
    if (first_free == nullptr)
    {
        return;
    }

    //判断size为1
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

template <typename T>
void StrVecTemp<T>::free()
{
    //先判断elements是否为空
    if (elements == nullptr)
    {
        return;
    }

    auto dest = elements;
    //遍历析构每一个对象
    for (size_t i = 0; i < size(); i++)
    {
        // destroy 会析构每一个元素
        alloc.destroy(dest++);
    }
    //再整体回收内存
    alloc.deallocate(elements, cap - elements);
    elements = nullptr;
    cap = nullptr;
    first_free = nullptr;
}

template <class T>
template <class... Args>
void StrVecTemp<T>::emplace_back(Args &&...args)
{
    chk_n_alloc();
    alloc.construct(first_free++, forward<Args>(args)...);
}

// forward既扩展了模板参数包Args，又扩展了函数参数包args
// std::forward<Args>(args)... 等价于std::forward<Ti>(ti)

//比如传递给emplace_back(10,'c');
//相当于调用 alloc.construct(first_free++, forward<int>(10), forward<char>('c'))
//调用的就是插入cccccccccc

template <typename... Args>
void fun(Args &&...args)
{
    // work 既扩展Args又扩展函数参数包args
    work(std::forward<Args>(args)...);
}

extern void test_strvectmp();

#endif