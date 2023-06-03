/*避免使用vector<bool>
做为一个STL容器，vector<bool>确实只有两个问题。第一，它不是一个STL容器。第二，它并不容纳bool。
*/
#include<vector>
#include <iostream>
#include <bitset>
#include <string>
using namespace std;
int main()
{
   // vector<bool> v;
   // bool *p=&v[0];//error 
    bitset<7> bst1;
    bitset<7> bst2;
    cout << "1) " << bst1 << endl; //输出 1) 0000000
    bst1.set(0,1);//将第0位变成1，bst1变为 0000001
    cout << "2) " << bst1 << endl; //输出 2) 0000001
    bst1 <<= 4; //左移4位，变为 0010000
    cout << "3) " << bst1 << endl; //输出 3) 0010000
    bst2.set(2);//第二位设置为1，bst2变成  0000100
    bst2 |=bst1; // bst2变成  0010100
    cout << "4) " << bst2 << endl; //输出 4) 0010100
    cout << "5) " << bst2.to_ulong () << endl; //输出 5) 20
    bst2.flip(); //每一位都取反，bst2变成 1101011
    bst1.set(3); //bst1变成  0011000
    bst2.flip(6); //bst2变成 0101011
    bitset<7> bst3 = bst2^ bst1;//bst3 变成 0110011
    cout << "6) " << bst3 << endl; //输出 6) 0110011
    cout << "7) " << bst3[3] << "," << bst3[4] << endl; //输出 7) 0,1
    return 0;
}
/*
bitset 有许多成员函数，有些成员函数执行的就是类似于位运算的操作。bitset 成员函数列表如下：
bitset <N> & operator &= (const bitset <N> & rhs);  //和另一个 bitset 对象进行与操作
bitset <N> & operator |= (const bitset <N> & rhs);  //和另一个 bitset 对象进行或操作
bitset <N> & operator ^= (const bitset <N> & rhs);  //和另一个 bitset 对象进行异或操作
bitset <N> & operator <<= (size_t num);  //左移 num 位
bitset <N> & operator >>= (size_t num);  //右移 num 位
bitset <N> & set();  //将所有位全部设成 1
bitset <N> & set(size_t pos, bool val = true);  //将第 pos 位设为 val
bitset <N> & reset();  //将所有位全部设成0
bitset <N> & reset (size_t pos);  //将第 pos 位设成 0
bitset <N> & flip();  //将所有位翻转（0变成1，1变成0）
bitset <N> & flip(size_t pos);  //翻转第 pos 位
reference operator[] (size_t pos);  //返回对第 pos 位的引用
bool operator[] (size_t pos) const;  //返回第 pos 位的值
reference at(size_t pos);  //返回对第 pos 位的引用
bool at (size_t pos) const;  //返回第 pos 位的值
unsigned long to_ulong() const;  //将对象中的0、1串转换成整数
string to_string () const;  //将对象中的0、1串转换成字符串（Visual Studio 支持，Dev C++ 不支持）
size_t count() const;  //计算 1 的个数
size_t size () const;  //返回总位数
bool operator == (const bitset <N> & rhs) const;
bool operator != (const bitset <N> & rhs) const;
bool test(size_t pos) const;  //测试第 pos 位是否为 1
bool any() const;  //判断是否有某位为1
bool none() const;  //判断是否全部为0
bitset <N> operator << (size_t pos) const;  //返回左移 pos 位后的结果
bitset <N> operator >> (size_t pos) const;  //返回右移 pos 位后的结果
bitset <N> operator ~ ();  //返回取反后的结果
bitset <N> operator & (const bitset <N> & rhs) const;  //返回和另一个 bitset 对象 rhs 进行与运算的结果
bitset <N> operator | (const bitset <N> & rhs) const;  //返回和另一个 bitset 对象 rhs 进行或运算的结果
bitset <N> operator ^ (const bitset <N> & rhs) const;  //返回和另一个 bitset 对象 rhs 进行异或运算的结果
*/