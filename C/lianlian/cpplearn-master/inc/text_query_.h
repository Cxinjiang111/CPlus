#ifndef __TEXT_QUERY_H_
#define __TEXT_QUERY_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <set>
using namespace std;
extern void runQueries(ifstream &infile);
class QueryResult;

class TextQuery
{
public:
    using line_no = std::vector<string>::size_type;
    TextQuery(ifstream &ifile);
    TextQuery() = default;
    QueryResult query(const string &str) const;

private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

class QueryResult
{
public:
    friend std::ostream &print(std::ostream &os, const QueryResult &qr);
    QueryResult(std::string s, shared_ptr<set<TextQuery::line_no>> p,
                shared_ptr<vector<string>> f) : sought(s), lines(p), file(f) {}

private:
    //查询的单词
    std::string sought;
    //出现的行号
    shared_ptr<set<TextQuery::line_no>> lines;
    //输入的文件
    shared_ptr<vector<string>> file;
};
#endif