//迭代器的移动能力，影响了这个算法的效率，所以设计为双层架构
//分派函数
#include<iterator>
#include<iostream>
#include<type_traits>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
using namespace std;
//一下实验时报
template<class RadomAccessIterator,class T>
void __Rotate_cycle(RadomAccessIterator first,RadomAccessIterator last,RadomAccessIterator initial,T*);
template<class  EuclideanRingElement>
EuclideanRingElement __Gcd(EuclideanRingElement m,EuclideanRingElement n);

template<class ForwardIterator>
inline void Rotate(ForwardIterator first,ForwardIterator middle,ForwardIterator last)
{
    if(first==middle||middle==last)
        return ;
                                      
    __Rotate(first,middle,last,std::__iterator_category(first));
}
//根据不同的迭代器类型完成三个旋转操作
template<class ForwardIterator>
inline void __Rotate(ForwardIterator first,ForwardIterator middle,ForwardIterator last,
                    forward_iterator_tag)
{
    for(ForwardIterator i=middle;;)
    {
        iter_swap(first,i);
        ++first;
        ++i;
        //可能结
        if(first==middle)
        {
            if(i==last)
            return ;
            middle=i;
        }
        else if(i==last)
        {
            i=middle;
        }
    }
    cout<<"ForwardIterator"<<endl;
}
// //双向迭代器
// template<class BidirectionalIterator,class Distance>
// inline void __rotate(BidirectionalIterator first,BidirectionalIterator middle,BidirectionalIterator last,
//                     Distance*,bidirectional_iterator_tag)
// {
//     reverse(first,last);
//     reverse(first,middle);
//     reverse(middle,last);    
//     cout<<"BidirectionalIterator"<<endl;
// }
//随机访问迭代器
template<class RandomAccessIterator,class Distance>
inline void __Rotate(RandomAccessIterator first,RandomAccessIterator middle,RandomAccessIterator last,
                    random_access_iterator_tag)
{
    Distance n=__Gcd(last-first,middle-first);
    while(n--)
    {
        __Rotate_cycle(first,last,first+n,middle-first,value_type(first));
    }
        cout<<"randomAccessIteraot"<<endl;
}
template<class RadomAccessIterator,class Distance,class T>
void __Rotate_cycle(RadomAccessIterator first,RadomAccessIterator last,RadomAccessIterator initial,Distance shift,T*)
{

    T value=*initial;
    RadomAccessIterator ptr1=initial;
    RadomAccessIterator ptr2=ptr1+shift;
    while(ptr2!=initial)
    {
        *ptr1=*ptr2;
        ptr1=ptr2;
        if(last-ptr2>shift)
        {
            ptr2+=shift;
        }
        else{
            ptr2=first+(shift-(last-ptr2));
        }
        *ptr1=value;
    }
}
template<class  EuclideanRingElement>
EuclideanRingElement __Gcd(EuclideanRingElement m,EuclideanRingElement n)
{
    while(n!=0)
    {
        EuclideanRingElement t=m%n;
        m=n;
        n=t;
    }
    return m;
}
void test01()
{
    //
    vector<int> a={1,2,3,4,5,6};
    typedef vector<int>::iterator iter;
    iter first=a.begin();
    iter middle=first+4;   
    iter last=a.end(); 
    Rotate(first,middle,last);
    for(auto it:a)
    {
        cout<<it<<"\t";
    }
}
int main()
{
    test01();
    return 0;
}

