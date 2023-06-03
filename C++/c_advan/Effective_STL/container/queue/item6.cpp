/*警惕C++最令人惱怒的解析
*/

#include<fstream>
#include<istream>
#include<list>
#include<iterator>
using namespace std;
void f()
{
    ifstream dataFile("int.txt");
    list<int> data(istream_iterator<int>(dataFile),istream_iterator<int>());//警告，這完全的並不是像你想想的的那樣

}
int f(double d);//申明  1
int f(double (d));//    2 
int f(double);//        3
//g帶有一個參數，那個參數是只想一個沒有參數，返回double的函數的指針
int g(double (*pf)());//g帶有一個只想函數的指針作爲參數
int g(double pf()); // 同上，pf其實是一個指針
int g(double()); 

list<int> data(istream_iterator<int>(dataFile),istream_iterator<int>());
//返回值list<int> 
//函數名data 
//參數為dataFile ，類型為istream_iterator<int>
//第二個參數沒有名字，他的類型是指向一個沒有參數而且返回istream_iterator<int>()的函數指針


class Widget{};
Widget w();
//这并没有声明一个叫做w的Widget，它声明了一个叫作w的没有参数且返回Widget的函数。

/*
一个更好的解决办法是在数据声明中从时髦地使用匿名istream_iterator对象后退一步，仅仅给那些迭代器名字
*/
int main()
{
    ifstream dataFile("ine.txt");
    istream_iterator<int> dataBegin(dataFile);
    istream_iterator<int> dataEnd;
    list<int> data(dataBegin,dataEnd);//這樣就相當於調用函數的形式了，
    //而不會被默認為函數申明

}