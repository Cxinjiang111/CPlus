#include<string>
#include<set>
#include<iterator>
#include<iostream>
using namespace std;
//自定義排序規則
struct StringPtrLess:public binary_function<const string*,const string*,bool>{
    bool operator()(const string*ps1,const string*ps2)const
    {
        return *ps1<*ps2;
    }
};
//
struct StringDeference{
    template<typename T>
    const T& operator()(const T*ptr)const
    {
        return *ptr;
    }
};
template<typename T>
struct StringPtrLess:public binary_function<const T*,const T*,bool>{
    bool operator()(const R*ps1,const T*ps2)const
    {
        return *ps1<*ps2;
    }
};
int main()
{
    // 内容類型       比較規則         分配器
    set<string*,less<string*>,allocator<string*> > ssp;
    //
    typedef set<string*, StringPtrLess> stringPtrSet;
    stringPtrSet ssp1;

    transform(ssp.begin(),ssp.end(),ostream_iterator<string>(cout,"\n"));

    return 0;
}