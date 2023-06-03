#include<iostream>
using namespace std;
template<class T,size_t N>
struct block{
    T data[N];                          //成员变量
    //迭代器型别
    typedef T                   value_type;//block内的对象型别
    typedef T*                  pointer;
    typedef const value_type*   const_pointer;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef ptrdiff_t           difference_type;
    typedef size_t              size_type;//用来表示block中的元素个数或是某特定元素的索引值
    typedef pointer             iterator;//指针
    typedef const_pointer       const_iterator;
    //功能
    iterator        begin(){return data;}
    iterator        end()  {return data+N;}
    const_iterator  begin()const{return data;}
    const_iterator  end()const  {return data+N;}
    reference operator[](size_type n){return data[n];}
    const_reference operator[](size_type n)const{return data[n];}
    size_type       size(){return N;}
    //补充逆向迭代器 带嵌套型别的迭代器
    typedef reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef reverse_iterator<iterator>          reverse_iterator;
    reverse_iterator rbegin()   {return reverse_iterator(end());}
    reverse_iterator rend()     {return reverse_iterator(begin());}    
    const_reverse_iterator rbegin()const   {return const_reverse_iterator(end());}
    const_reverse_iterator rend()const     {return const_reverse_iterator(begin());}    
    //
    size_type size(){return N;}

    bool empty(){return N==0;}
    void swap(block&x)
    {
        for(size_t n=0;n<N;++n)
            std::swap(x.data[n],data[n]);
    }


};
////随机访问容器是一种可逆向的容器
/*
block的元素个数是其型别的一部分，block<int,10> 与block<int,12>是完全不同的型别。
元素个数在编译期就固定不变了。 你不能对block增加新元素， 将block<int,10>赋值给block<int，10>，
 或是以block<int,12>作为引数、传入预期获得block<int,10>的函数。
block 的元素个数是该block的一个template引数， 而非可以在constructor中指定的值。
这是所谓的「template非型别参数(nontype template parameter)」， 是语言自身的一个特性。
 是的， block的第二个template参数并非一个型别， 而是一个数值。 C+＋语言当初加进template特性时，
「template非型别参数」就已经成为语言的一部分了，不过却很少被用到。然而它对千本例非常重要。
 在block内部，template参数 N 被视为编译期常量， 可用在编译期常量可运用的任何地方（此例之 中， 它被当作数组的元素个数）。
  这使block的member variable data不只是个指向数组的指针， 而且可以代表数组自身。 block的所有元素都分配千一块连续存储空间， 因此称为"block” 。
block之所以不寻常的第二个理由是， 它遗漏了很多东西： 没有constructor、没有destructor、 没有 assigrunent操作符。
 这或许不那么令人惊讶， 因为由编译器产生的每 －个member functions的缺省版 都不赖。 将某个block赋值给另一 block, 意味赋予其所有元素。
 较不寻常的是， block甚至没有任 何public声明或private声明。block是个struct, 其所有成员， 包含数组data自身， 都是public。
这似乎违反封装(encapsulation)概念， 不过在这个特别的案例中并不会造成任何伤害。 
令data成为public, 可允许客户独立更动data内的元素， 然而客户本就可以以其他方式更动之（例如通过 iterators或使用opera 七or[])。 
毕竟， 这是整个block的要点。令data成为public, 除了「不会造成任何伤害」之外， 其实还有个特别而必要的理由。
 是的， 在C 语言中， 你可以像对数组做初始化动作一般地（也就是在一对大刮号内放置一串初值）， 将struct初 始化。
 C+＋的情况也一样，不过得符合某种特殊限制：struct不能拥有使用者声明的任何constructor,
也不能拥有任何pirvate或protected members 1 O。 block满足这些限制， 所以我们可以像对数组一般地声明一个block:

*/
//还有两个operator== 和operator< 这个没有写到类中，而是全局
template<class T,size_t N>
bool operator==(const block<T,N> &x,const block<T,N>&y)
{
    for(size_t n=0;n<N;++n)
    {
        if(x[n]!=y[n])
            return false;
    }
    return true;
}
template<class T,size_t N>
bool operator<(const block<T,N> &x,const block<T,N>&y)
{
    for(size_t n=0;n<N;++n)
    {
        if(x[n]<y[n])
            return true;
        else if(x[n]>y[n])
            return false;
    }
    return true;
}
int main()
{
    block<int,10> a={1,2,3,4,5};
    cout<<a[3]<<endl;
    return 0;
}