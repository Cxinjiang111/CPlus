/*
trivial iterator 是一种可dereference （*），使得以取用某个object的concept，他不必支持数值运算如累加与比较。
.	Definitions（定义）
1.	某型别如果是TrivialIterator的一个model,那么它可以是mutable（可变的），意味该型别的 
object所指之值可以被更改。它也可以是constant（不变的），意味该型别的object所指之值
不能被更改。举例来说，int＊是mutableiterator type,而canstint*是constantiterator type。 
如果某个iterator是mutable,则其valuetype必然是Assignable的一个model,反之不成立。

2.Trivial Iterator可能拥有一个singular值，意味对千大多数操作行为，包括相等性(equality)比较，
其结果未有定义。它唯一保证支持的操作行为是「将一个nonsingulariterator赋予一个 singular iterator」。

3.	Trivial Iterator可以拥有可提领值(dereferenceablevalue)，意味提领动作将产生出明确定义的结 果。
可提领的iterators都是nonsingular,反之则不成立。以past-the-end指针为例，它紧邻数 组的尾端，虽然不可提领，
却是nonsingular（因为它与特定数组产生关联，而且有明确定义的操 作行为作用于其上）。

4.「令某个可提领的iterator无效」意指执行某种行为之后，该iterator可能变成无法提领，
或是变成singular。举个例子，如果p是个指针，则deletep便是令p不再有效。
*/
#include<iostream>
using namespace std;
int main()
{
    int a[5]={8,2,3,4,5};
    int *p=a;
    ++p;
    cout<<*p<<endl;
    int b=6;
    p=&b;
    p++;
    cout<<*p<<endl;
    return 0 ;
}