/*
条款28：了解如何通过reverse_iterator的base得到iterator
*/
#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>
using namespace std;
int main()
{
    vector<int> v;
    v.reserve(5);
    for(unsigned i=0;i<5;++i)
    {
        v.push_back(i);
    }
    // for(unsigned i=0;i<5;++i)
    // {
    //     cout<<v[i]<<endl;
    // }
    vector<int>::reverse_iterator ri=find(v.rbegin(),v.rend(),0);
    //vector<int>::iterator ii(ri);//error
    vector<int>::iterator ii(ri.base());// base 实际上是向前了一位 这种特的偏移量为1
    vector<int>::iterator ii1(--ri.base());// 这样就可可以避免这个偏移量了
    vector<int>::iterator ii2((++ri).base());//这和上面一样  这样还不会报错。。。。
    //不过reverse_iterator 可以向iterator转化 
    cout<<*ii2<<endl;
    /*
这张图很好，显示了reverse_iterator和它对应的base iterator之间特有的偏移量，就像rbegin()和rend()与相关的
begin()和end()一样，但并没有说出了所有你需要知道的东西。特别是，它并没有解释怎样在ri上实现你在i上
想要完成的操作。正如条款26解释的，有些容器的成员函数只接受iterator类型的参数，所以如果你想要在ri所
指的位置插入一个新元素，你不能直接这么做，因为vector的insert函数不接受reverse_iterator。如果你想要删
除ri所指位置上的元素也会有同样的问题。erase成员函数会拒绝reverse_iterator，坚持要求iterator。为了完成
删除和一些形式的插入操作，你必须先通过base函数将reverse_iterator转换成iterator，然后用iterator来完成工
作。
    */

    //vector<int>::iterator ri=find(v.begin(),v.end(),2);
   // vector<int>::reverse_iterator ii(ri.base());//error
    //cout<<*ii<<endl;
    //但是不能从iterator 向reverse_iterator转化
    return 0;
}