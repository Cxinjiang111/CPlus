#ifndef __POINTER_H__
#define __POINTER_H__
#include <string>
#include <vector>
#include <memory>
using namespace std;
extern void use_pointer();
extern void use_sharedptr();
extern void test_StrBlob();
extern void shared_ptrnew();
extern void bad_use_sharedptr();
extern void reset_shared();
extern void delfunc_shared();
extern void use_uniqueptr();
extern void use_weakptr();
class StrBlob
{
public:
    //定义类型
    typedef std::vector<string>::size_type size_type;
    StrBlob();
    //通过初始化列表构造
    StrBlob(const initializer_list<string> &li);
    //拷贝构造函数
    StrBlob(const StrBlob &sb);
    StrBlob &operator=(const StrBlob &sb);

    //返回vector大小
    size_type size() const { return data->size(); }
    //判断vector是否为空
    bool empty()
    {
        return data->empty();
    }
    //向vector写入元素
    void push_back(const string &s)
    {
        data->push_back(s);
    }

    //从vector弹出元素
    void pop_back();
    //访问头元素
    std::string &front();
    //访问尾元素
    std::string &back();
    //打印引用数
    void printCount();

private:
    shared_ptr<vector<string>> data;
    //检测i是否越界
    void check(size_type i, const string &msg) const;
    std::string badvalue = "";
};
#endif