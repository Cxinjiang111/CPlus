/*
条款29：需要一个一个字符输入时考虑使用istreambuf_iterator
*/
#include<fstream>
#include<string>
#include<iostream>
#include<iterator>
using namespace std;
void t1()
{
    ifstream inputfile("interstingData.txt");
    string fileData((istream_iterator<char>(inputfile)),istream_iterator<char>());
    //那是因为istream_iterators使用operator>>函数来进行真的读取，而且operator>>函数在默认情况下忽略空格。
    cout<<fileData<<endl;//helloworld 确实没法把文本中的空格给读进去
}
void t2()
{
    ifstream inputfile("interstingData.txt");
    //inputfile.unset(ios::skipws);//目前C++11 没有unset函数
    string fileDate((istream_iterator<char>(inputfile)),istream_iterator<char>());
    /*
唉，你会发现它们的拷贝速度不像你想象的那么快。istream_iterators所依靠的operator>>函数进行的是格式化
输入，这意味着每次你调用的时候它们都必须做大量工作。它们必须建立和销毁岗哨（sentry）对象（为每个
operator>>调用进行建立和清除活动的特殊的iostream对象），它们必须检查可能影响它们行为的流标志（比
如skipws），它们必须进行全面的读取错误检查，而且如果它们遇到问题，它们必须检查流的异常掩码来决
定是否该抛出一个异常。如果进行格式化输入，那些都是重要的活动，但如果你需要的只是从输入流中抓取
下一个字符，那就过度了。
    */
}
void t3()
{
    ifstream inputfile("interstingData.txt");
    //已缓冲区的形式，不在是单个字符复制 然后检查
    string fileData((istreambuf_iterator<char>(inputfile)),istreambuf_iterator<char>());
    std::cout<<fileData<<endl;
/*
一个更高效的方法是使用STL最好的秘密武器之一：istreambuf_iterators。你可以像istream_iterator一样使用
istreambuf_iterator，但istream_iterator<char>对象使用operator>>来从输入流中读取单个字符。
istreambuf_iterator<char>对象进入流的缓冲区并直接读取下一个字符。（更明确地说，一个
istreambuf_iterator<char> 对象从一个istream s中读取会调用s.rdbuf()->sgetc()来读s的下一个字符。）把我们的文
件读取代码改为使用istreambuf_iterator相当简单
*/
}
int main()
{

    t3();
    //method 2


    return 0;
}






