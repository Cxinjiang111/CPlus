#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;
template<class T>
struct display{
    void operator()(const T&x)
    {
        cout<<x<<"\t";
    }
};
int main()
{
    {
        int ia[]={0,1,2,3,4,5,6,7,8};
        copy(ia+2,ia+7,ia);
        for_each(ia,ia+sizeof(ia)/sizeof(int),display<int>());
        cout<<endl;
        //0,      1,      2,      3,      4,      5,      6,      7,     8
        //2       3       4       5       6       5       6       7       8
    }
    cout<<"========="<<endl;
    {
        int ia[]={0,1,2,3,4,5,6,7,8};
        copy(ia+2,ia+7,ia+4);//可能越界，
        for_each(ia,ia+sizeof(ia)/sizeof(int),display<int>());
        cout<<endl;
        //0,      1,      2,      3,      4,      5,      6,      7,     8
        //0       1       2       3       2       3       4       5       6
    }
    cout<<"========="<<endl;
    {
        int ia[]={0,1,2,3,4,5,6,7,8};
        deque<int> id(ia,ia+9);
        deque<int>::iterator first=id.begin();
        deque<int>::iterator last=id.end();
        advance(first,2);
        cout<<*first<<endl;//2
        advance(first,-2);
        cout<<*first<<endl;// 0
        deque<int>::iterator result=id.begin();
        cout<<*result<<endl;//0 
        copy(first,last,result);
        for_each(id.begin(),id.end(),display<int>());
        cout<<endl;
        //0       1       2       3       4       5       6       7       8
    }

}














