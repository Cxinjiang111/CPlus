//将线性查找一般化
//find我们已经将两种东西参数化了，1：查找对象的型别（模板），2：该种对象再数据结构中的组织方式（对外以迭代器形式去处理任意一种数据结构）
//find就是查找某个等于引数T的元素，
//T特指参数模板，pred则指函数模板 这里并不一定非得使用函数指针不可，可以被操作符operator()重载，仿函数型别

#include<iostream>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
template<class InputIterator,class Predicate>//Predicate 为预测的函数 比find更为一般化，寻找某个满足pred条件的元素， 
InputIterator Find_if(InputIterator first,InputIterator last,Predicate pred)
{
    while (first!=last)
    {
        if(!pred(*first))
            ++first;
        else
        break;
    }
    return first;
}
//传入就是函数指针
template<class T>
bool Is_even(T x)
{
    return (x&1)==0;
}
//函数重载
template<class T>
struct IIs_Even{
    bool operator()(T x)const{
        return (x&1)==0;
    }
};
struct Person{
    string last_name;
};
//我们以find_if来查找满足此一条件的元素 这便是完全一般化的函数对象，
//它拥有局部状态，以及一个constructor 而由于具有operator(),使得其对象看起来就像个函数，接受一个型别为Person的引数并返回bool值
struct last_name_is{
    string value;
    last_name_is(const string&val):value(val){}
    bool operator()(const Person &x){
        return x.last_name==value;
    }
};
void t1()
{

    vector<int> a={1,2,3,4};
    vector<int>::iterator first=a.begin();
    vector<int>::iterator last=a.end();
    vector<int>::iterator it;
    it=find_if(first,last,Is_even<int>);
    Find_if(first,last,Is_even<int>);//
    Find_if(first,last,IIs_Even<int>());
    //find_if(first,last,last_name_is(Person("smith")));
}

