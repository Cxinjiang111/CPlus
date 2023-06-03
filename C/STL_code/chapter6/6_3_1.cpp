#include<numeric>
#include<iostream>
#include<vector>
#include<functional>
#include<iterator>
using namespace std;
template<typename T>
class Multi{
    T operator()(T&lhs,T&rhs){
        return lhs*rhs;
    }
};
int main()
{
    int ia[5]={1,2,3,4,5};
    vector<int> v(ia,ia+5);
    //accumulate通过以此累计遍历的方式，可以自定义操作函数 
    cout<<accumulate(v.begin(),v.end(),1)<<endl;//1+2+3+4+5=16
    for_each(v.begin(),v.end(),[](int i){cout<<i<<"\t";});
    cout<<"-==== accumulate ========"<<endl;
//1       2       3       4       5       -==== accumulate ========
    //for_each(v.begin(),v.end(),ostream_iterator<int>(cout,"\n"));
    cout<<accumulate(v.begin(),v.end(),1,minus<int>())<<endl;//1-2-3-4-5-6=-14
    
    for_each(v.begin(),v.end(),[](int i){cout<<i<<"\t";});
    cout<<"-======accumulate  minus======"<<endl;
//1       2       3       4       5       -======accumulate  minus======
    //默认是内积的形式，两个数先加然后两个数再相乘
    cout<<inner_product(v.begin(),v.end(),v.begin(),10)<<endl; // 1*1+2*2+3*3+4*4+5*5+10=65 
    for_each(v.begin(),v.end(),[](int i){cout<<i<<"\t";}); 
        cout<<"-=====inner_product======="<<endl;
//1       2       3       4       5       -=====inner_product=======
    //这个就是按照自己特定的两个函数进行操作
    //0-(1+1)-(2+2)-(3+3)-(4+4)-(5+5)+10=-20
    cout<<inner_product(v.begin(),v.end(),v.begin(),10,minus<int>(),plus<int>());// -20
    for_each(v.begin(),v.end(),[](int i){cout<<i<<"\t";}); 
        cout<<"-====inner_product   minus<int>(),plus<int>() ========"<<endl;
//1    2       3       4       5       -====inner_product   minus<int>(),plus<int>() ========
    //一下这个迭代器将绑定到cout 作为输出用
    ostream_iterator<int> oite(cout," ");
    //oite 输出迭代器
    //局部性操作函数
    partial_sum(v.begin()+2,v.end(),oite);
    cout<<"-====  partial_sum  ========"<<endl;
    //3 3+4 3+4+5
    //3  7   12 -====  partial_sum  ========
    /*
     template<typename _InputIterator, typename _OutputIterator>
    _OutputIterator partial_sum(_InputIterator __first, _InputIterator __last,_OutputIterator __result)
    {
        if (__first == __last)
            return __result;
        while (++__first != __last)
        {
            __value = _GLIBCXX_MOVE_IF_20(__value) + *__first;
            *++__result = __value;
        }
      return ++__result;
    }
    */
       partial_sum(v.begin()+2,v.end(),oite,minus<int>());
        cout<<"-====  partial_sum  minus<int>() ========"<<endl;
    //  3 -1 -6 -====  partial_sum  minus<int>() ========

    /*
      template<typename _InputIterator, typename _OutputIterator,typename _BinaryOperation>
    partial_sum(_InputIterator __first, _InputIterator __last,_OutputIterator __result, _BinaryOperation __binary_op)
    {
      if (__first == __last)
	        return __result;
        while (++__first != __last)
        {
            __value = __binary_op((__value), *__first);
            *++__result = __value;
        }
        return ++__result;
    }
    */
   
   adjacent_difference(v.begin(),v.end(),oite,minus<int>());
    cout<<"-====  adjacent_difference  minus<int>() ========"<<endl;
    //(#1)元素照录，(#n)新元素等于(#n)旧元素-(#n-1)旧元素)
    //1 1 1 1 1 -====  adjacent_difference  minus<int>() ========    
    adjacent_difference(v.begin(),v.end(),oite,plus<int>());
    cout<<"-====  adjacent_difference  minus<int>() ========"<<endl;
    //1 1+2 2+3 3+4 4+5 
    //1 3 5 7 9 -====  adjacent_difference  minus<int>() ========
    
    
    adjacent_difference(v.begin(),v.end(),oite);
    cout<<"-====  adjacent_difference  ========"<<endl;
    //1 1 1 1 1 -====  adjacent_difference  ========    
    return 0;
}





