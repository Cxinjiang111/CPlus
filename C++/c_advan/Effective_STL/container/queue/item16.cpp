#include<string>
#include<iostream>
#include<vector>
#include<deque>
#include<list>
#include<set>
using namespace std;
void doSomething(const char*pString);
void doSomething1(const int*pString);
size_t fillArray(double *pArray,size_t arraySize);
size_t fillString(char *pArray,size_t arraySize);
int main()
{
    string s("hello");
    vector<int> v;
    doSomething(s.c_str());//s.c_str() 返回一個const char* 指針
    doSomething1(&v[0]);
    //如果你想用C风格API返回的元素初始化一个vector,這麽做不會出問題是因爲vector和數組都有相同的内存分佈
    int maxNumDoubles=100;
    vector<double> vd(maxNumDoubles);
    vd.resize(fillArray(&vd[0],vd.size()));
    
    deque<double>  d(vd.begin(),vd.end());
    list<double> l(vd.begin(),vd.end());
    set<double> s(vd.begin(),vd.end());
}







