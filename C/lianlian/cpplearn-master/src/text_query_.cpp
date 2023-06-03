#include "../inc/text_query_.h"
#include <iostream>
#include <string>
#include <istream>
#include <sstream>

using namespace std;
void runQueries(ifstream &infile)
{
    //根据输入文件构建一个TextQuery对象
    TextQuery tq(infile);
    //根据输入的单词返回查询结果
    while (true)
    {
        cout << "enter word to look for, or q to quit" << endl;
        //输入单词查询结果，或者输入q退出循环,或者遇到终止退出。
        string s;
        if (!(cin >> s) || s == "q")
            break;
        print(cout, tq.query(s)) << endl;
    }
}

TextQuery::TextQuery(ifstream &infile) : file(make_shared<vector<string>>())
{
    string text;
    //按行读取文件内容写入text
    while (getline(infile, text))
    {
        //将一行的内容写入vector file中
        file->push_back(text);
        //统计行号，vector的大小-1就是行号
        int n = file->size() - 1;
        //将字符串构造为string流
        istringstream line(text);
        string word;
        //将字符串中的单词依次写入word
        while (line >> word)
        {
            auto &lineset = wm[word];
            //如果单词不在wm中，返回的就是空指针
            if (!lineset)
            {
                //重新构造一个set，让智能指针绑定他
                lineset.reset(new set<line_no>());
            }
            lineset->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string &str) const
{
    //根据单词去map中查找
    auto findval = wm.find(str);
    //构造一个指向空的set的指针
    static auto nodata = make_shared<set<line_no>>();
    if (findval == wm.end())
    {
        return QueryResult(str, nodata, file);
    }

    return QueryResult(str, findval->second, file);
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    //依次输出单词，出现次数
    os << qr.sought << " occurs " << qr.lines->size() << " times" << endl;
    //打印出现的每一行
    for (auto num : *(qr.lines))
    {
        os << "\t line( " << num + 1 << " ) " << *(qr.file->begin() + num) << endl;
    }
    return os;
}
