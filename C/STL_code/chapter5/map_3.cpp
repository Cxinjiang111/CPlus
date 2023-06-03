#include<map>
#include<iostream>
#include<string>
using namespace std;
int main(){
    map<string,int> simap;
    simap[string("jhou")]=1;
    simap[string("jerr")]=2;
    simap[string("jason")]=3;
    simap[string("jimmy")]=4;

    pair<string,int> value(string("david"),5);
    simap.insert(value);
    map<string,int>::iterator simp_iter=simap.begin();
    for(;simp_iter!=simap.end();simp_iter++){
        cout<<simp_iter->first<<"\t"<<simp_iter->second<<endl;
    }
    return 0;
}
/*
我想针对其中使用的insert（）函数及subscript（下标）操作符做一些说明。首先是insert()函数：
／注意以下insert操作返回的型别
pair<iterator,bool> insert(const value—type&x)
{ return t.insert_unique(x); }
就是和set一样 之所以不重复就是因为 插入时选择insert_unique函数，
此式将工作直接转给底层机制RB-tree的inser七＿unique()去执行，原也不必多说。要注意的是其返回值型别是一个pair,由一个迭代器和一个bool值 组成，后者表示插入成功与否，成功的话前者即指向被插入的那个元素。
至于subscript（下标）操作符，用法有两种，可能作为左值运用（内容可被修改），也可能作为右值运用（内容不可被修改），例如：
*/

