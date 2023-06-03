#include<iterator>
#include<algorithm>
#include<type_traits>
using namespace std;
template<class ForwardIterator,class T>
ForwardIterator find(ForwardIterator first,ForwardIterator last,const T&value)
{
    while (first!=last)
    {
        ++first;
        if(*first==value)
        return first;
    }
    return last;
}
template<class ForwardIterator,class BinaryPredicate>
ForwardIterator find_if(ForwardIterator first,ForwardIterator last,BinaryPredicate binary_pred)
{
    while (first!=last)
    {
        ++first;
        if(binary_pred(*first))
        return first;
    }
    return last;
}
//由于只有双向迭代器才会有这种逆向的功能，所以这里将其设计为双层架构，
template<class ForwardIterator1,class ForwardIterator2>
inline ForwardIterator1 find_end(ForwardIterator1 first1,ForwardIterator1 last1,ForwardIterator1 first2,ForwardIterator1 last2)
{
    typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;//产生迭代器类型的临时对象，再利用编译器的参数推导机制，自己调用某个对应函数
    typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;    
    return __find_end(first1,last1,first2,last2,category1(),category2());
    //category1()型别名称 之后直接加上一对小括号，便会产生一个临时对象
}
//前向迭代器版本
template<class ForwardIterator1,class ForwardIterator2>
inline ForwardIterator1 __find_end(ForwardIterator1 first1,ForwardIterator1 last1,ForwardIterator1 first2,ForwardIterator1 last2,forward_iterator_tag,forward_iterator_tag)
{
    if(first1==last1)
        return last1;
    else{
        ForwardIterator1 result=last1;
        while (1)
        {
            ForwardIterator1 new_result=search(first1,last1,first2,last2);
            if(new_result==last1)
                return result;
            else{
                result=new_result;//
                first1=new_result;
                ++first1;
            }
        }
    }
}
//bidirectional iterators迭代器版本
template<class BidirectionalIterator1,class BidirectionalIterator2>
inline BidirectionalIterator1 __find_end(BidirectionalIterator1 first1,BidirectionalIterator1 last1,BidirectionalIterator2 first2,BidirectionalIterator2 last2,forward_iterator_tag,forward_iterator_tag)
{
    typedef reverse_iterator<BidirectionalIterator1> reviter1;
    typedef reverse_iterator<BidirectionalIterator2> reviter2;
    reviter1 rlast1(first1); //指向迭代器的位置 首标记为尾
    reviter1 rlast2(first2);
    reviter1 rresult=search(reviter1(last1),rlast1,reviter2(last2),rlast2);
    if(rresult==rlast1){
        return last1;
    }       
    else{
        BidirectionalIterator1 result=rresult.base();//逆向查找的位置
        advance(result,-distance(first2,last2));//将位置变换为前向迭代器的位置
        return result;
    }
}


