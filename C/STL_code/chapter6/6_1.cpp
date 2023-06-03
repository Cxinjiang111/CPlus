/* 所有泛型算法的前两个参数都是一对迭代器，通常称为first 和last 用以标示
算法的操作区间，习惯采用前闭后开区间，当first==end 表示空区间
将无效迭代器传给某个算法，虽然是一种错误，却不保证能够在编译时期就被捕捉出来
因为所谓 迭代器类型并不是真实的型别，他们只是function template的一种型别参数

质变算法 mutating algorithm 通常提供两个版本，一个是in-place就地进行版，就地改变其操作对象
另一个是copy版 将操作对象的内容复制一份副本 ，然后再副本上进行修改并返回该副本。

*/
#include<iostream>
using namespace std;

//数组的查找的函数,返回特定位置处的指针
int *find_(int*arrayHead,int arraySize,int value)
{
    int i=0;
    for(;i<arraySize;++i)
    {
        if(arrayHead[i]==value)
        {         
            return &(arrayHead[i]);
        }
    }

}
/*
指针们支持一下四种find()函数
inequality() 判断不相等操作符
deferfencelm 提领 取值操作符
prefix increment 前置式递增
copy  复制行为
、这就是一个完全泛型化的find函数
*/
template<class Iterator,class T>
T *find(Iterator begin,Iterator end,T value)
{
    while (begin!=end&&*begin!=value)
    {
        ++begin;
        /* code */
    }
    return begin;
}
void t1()
{
    const int arraySize=7;
    int ia[arraySize]={0,1,2,3,4,5,6};
    int *end=ia+arraySize;
    int *ip=find_(ia,sizeof(ia)/sizeof(int),3);
    int *ip1=find(ia+2,ia+5,3);//这种具有的优势就是可以自定义一个区间
    if(ip==end)
    {
        cout<<"not find "<<endl;
    }
    else{
        cout<<"3 has found"<<endl;
    }



}



