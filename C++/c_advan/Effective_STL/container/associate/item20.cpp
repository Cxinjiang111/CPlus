#include<string>
#include<set>
#include<iterator>
#include<iostream>
using namespace std;
int main()
{
    set<string*> ssp;
    ssp.insert(new string("anterate"));
    ssp.insert(new string("Wombat"));    
    ssp.insert(new string("Lemur"));
    ssp.insert(new string("Penguin"));

// for(set<string*>::iterator it=ssp.begin();it!=ssp.end();++it)
// {
//     std::cout<<*it<<endl;//去指針的值
//     std::cout<<*(*it)<<endl;//取指針只指向的值
// }
//ostream_iterator需要知道被打印的对象的类型，所以当你告诉它是一个string时（通过作为模板参数传递），编译器检测到那和
//ssp中储存的对象类型（是string*）之间不匹配，它们会拒绝编译代码。获得了额外的类型安全。
    copy(ssp.begin(),ssp.end(),ostream_iterator<string>(cout,"\n"));//這個編譯不過去
    return 0;
}