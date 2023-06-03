#pragma once 
#include <string>
#include <set>
#include <unordered_map>
using namespace std;
extern void test_strvec();

class StrVec
{
public:
    //无参构造函数
    StrVec() : elements(nullptr), first_free(nullptr),
               cap(nullptr) {}
    //拷贝构造函数
    StrVec(const StrVec &);

    //拷贝赋值运算符
    StrVec &operator=(const StrVec &);

    //移动构造函数
    //声明noexcept就是不抛出异常
    StrVec(StrVec &&src) noexcept : elements(src.elements), first_free(src.first_free), cap(src.cap)
    {
        //将src的成员设置为空
        src.elements = src.first_free = src.cap = nullptr;
    }

    //移动赋值运算符
    StrVec &operator=(StrVec &&);

    //析构函数
    ~StrVec();
    //拷贝元素
    void push_back(const std::string &);
    //抛出元素
    void pop_back(std::string &s);
    //返回元素个数
    size_t size() const { return first_free - elements; }
    //返回总容量
    size_t capacity() const { return cap - elements; }
    //返回首元素地址
    std::string *begin() const
    {
        return elements;
    }
    //返回第一个空闲元素地址
    //也是最后一个有效元素的下一个位置
    std::string *end() const
    {
        return first_free;
    }

private:
    //判断容量不足开辟新空间
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    //重新开辟空间
    void reallocate();
    // copy指定范围的元素到新的内存中
    std::pair<std::string *, std::string *> alloc_n_copy(
        const std::string *, const std::string *);
    //释放空间
    void free();
    //数组首元素的指针
    std::string *elements;
    //指向数组第一个空闲元素的指针
    std::string *first_free;
    //指向数组尾后位置的指针
    std::string *cap;
    //构造string类型allocator静态成员
    static std::allocator<std::string> alloc;
};

//返回对象的copy
extern StrVec get_vec_str();