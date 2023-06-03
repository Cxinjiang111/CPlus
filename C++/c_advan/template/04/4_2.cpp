#include<iostream>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
//如果f是个函数对象，我们可以将operator()施行于f身上
//单参与双参函数对象
template<class ForwardIterator, class BinaryPredicate>
ForwardIterator Adjacent_find(ForwardIterator first,ForwardIterator last,BinaryPredicate Pred)
{
    if(first==last)
        return last;
    ForwardIterator next=first;
    while (++next!=last)
    {
        if(Pred(*first,*next))
            return first;
        first=next;
    }
    return last;
}
bool is_equal(int x,int y)
{
    return x==y;
}
struct Is_equal{
    bool operator()(int x,int y)
    {
        return x==y;
    }
};
void t1()
{
    vector<int> a={1,4,4,5,7,2,4,5};
    vector<int>::iterator first=a.begin();
    vector<int>::iterator last=a.end();
    vector<int>::iterator it;

    //it=Adjacent_find(first,last,is_equal);//函数模板
    it=Adjacent_find(first,last,Is_equal());//仿函数
    cout<<*it<<endl;
}
int main()
{
    t1();
    return 0;
}



