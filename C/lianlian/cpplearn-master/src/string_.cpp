#include "../inc/string_.h"
#include <string>
#include <iostream>
using namespace std;
void str_func()
{
    //默认初始化,s1是一个空字符串
    string s1;
    //赋值初始化,s2是s1的副本
    string s2 = s1;
    //直接初始化 字面值初始化
    string s3 = "hiya";
    //直接初始化 构造函数初始化
    string s4(10, 'c');
    string s5("hello zack");
}

void opstr_func()
{
    //定义空字符串
    string s;
    //从输入流写入s
    cin >> s;
    //将s写入输出流
    cout << s << endl;
    //循环读取，直到遇到换行符或者非法输入
    // string world;
    // while (cin >> world)
    //     cout << world << endl;
    // //读取一整行
    // string linestr;
    // while (getline(cin, linestr))
    // {
    //     cout << linestr << endl;
    // }

    // //每次读入一整行，遇到空行跳过
    // while (getline(cin, linestr))

    // {
    //     if (!linestr.empty())
    //     {
    //         cout << linestr << endl;
    //         //打印字符串长度
    //         cout << linestr.size() << endl;
    //         // size()返回string::size_type类型的数据
    //         string::size_type size = linestr.size();
    //     }
    // }

    // 比较
    string str1 = "Hello";
    string str2 = "Hello W";
    string str3 = "Za";
    //依次比较每个字符，字符大的字符串就大
    auto b2 = str3 > str1;
    cout << b2 << endl;
    //前面字符相同，长度长的字符串大
    auto b = str2 > str1;
    cout << b << endl;
    // string类对象相加
    string s1 = "Hello", s2 = "Zack";
    string s3 = s1 + "," + s2 + '\n';
    cout << s3 << endl;
    //加号两侧至少有一个是string类型，否则报错
    // string s4 = "Hello" + "Zack";
}

void str11_func()
{
    string str("hello zack");
    //遍历输出str中的每个字符
    for (auto c : str)
    {
        cout << c << endl;
    }

    //统计字符串中标点符号的数量
    string s("Hello World!!!");
    decltype(s.size()) punct_cnt = 0;
    //统计s中标点符号的数量
    for (auto c : s)
    {
        if (ispunct(c))
            punct_cnt++;
    }
    cout << punct_cnt
         << " punctuation characters in "
         << s << endl;

    //将字符串变为大写
    string s3("Hello Vivo");
    for (auto &c : s3)
    {
        //通过引用string中的字符，然后修改字符
        c = toupper(c);
    }
    cout << s << endl;
    //通过下标索引修改字符串
    //把第一个单词变为大写
    string sind("some string");
    for (decltype(sind.size()) index = 0; index != sind.size() && isspace(sind[index]); ++index)
    {
        sind[index] = toupper(sind[index]);
    }
}
