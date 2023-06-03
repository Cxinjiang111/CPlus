#include<set>
#include<iostream>
#include<algorithm>
#include<iterator>
using namespace std;
template<class T>
struct dispaly{
    void operator()(const T&x)
    {
        cout<<x<<"\t";
    }
};
int main()
{
    int ia1[6]={1,3,5,7,9,11};
    int ia2[7]={1,1,2,3,5,8,13};
    multiset<int> s1(ia1,ia1+6);
    multiset<int> s2(ia2,ia2+7);
    for_each(s1.begin(),s1.end(),dispaly<int>());
    cout<<endl;
    for_each(s2.begin(),s2.end(),dispaly<int>());
    cout<<endl;

    multiset<int>::iterator first1=s1.begin();
    multiset<int>::iterator last1=s1.end();
    multiset<int>::iterator first2=s2.begin();
    multiset<int>::iterator last2=s2.end();

    set_union(first1,last1,first2,last2,ostream_iterator<int>(cout,"\t"));
    cout<<endl;

    first1=s1.begin();
    first2=s2.begin();
    cout<<"inserction of s1,s2"<<endl;

    set_intersection(first1,last1,first2,last2,ostream_iterator<int>(cout,"\t"));
    first1=s1.begin();
    first2=s2.begin();
    cout<<"symemetric difference of s1,s2"<<endl;
    
    set_symmetric_difference(first1,last1,first2,last2,ostream_iterator<int>(cout,"\t"));
    cout<<endl;
    first1=s1.begin();
    first2=s2.begin();
    cout<<" difference of s1,s2"<<endl;   

    set_difference(first1,last1,first2,last2,ostream_iterator<int>(cout,"\t"));
    cout<<endl;
    /*
1       3       5       7       9       11
1       1       2       3       5       8       13
1       1       2       3       5       7       8       9       11      13
inserction of s1,s2
1       3       5       symemetric difference of s1,s2
1       2       7       8       9       11      13
 difference of s1,s2
7       9       11
    */
}