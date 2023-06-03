/*
迭代器相应型别之五：iterator_category
最后一个（第五个）迭代器的相应型别会引发较大规模的写代码工程。
在那之前，我必须先讨论迭代器的分类。
根据移动特性与施行操作，迭代器被分为五类:
input iteraotr:这种迭代器所指的对象，不允许外界改变，只读 
output iterator：只写
forward iterator 允许”写入型“算法 在此钟迭代器所形成的区间上进行读写操作 
Bidirectional iterator:可双向移动，某些算法需要逆向走访某个迭代器区间，
前四种迭代器支持operator++, operator--
Random Access iterator:这种涵盖所有指针算术能力，包括p+n,p-n,p1-p2,p2<p1
//----------------------------
设计算法时，如果可能，我们尽量针对图3-2中的某种迭代器提供一个明确定义，
并针对更强化的某种迭代器提供另一种定义，这样才能在不同情况下提供最大效率。
在研究STL的过程中，每一分每一秒我们都要谨记在心，效率是个重要课题。
假设有个算法可接受ForwardIterator,你以RandomAccess Iterator喂给它，
 它当然也会接受，因为一个RandomAccess Iterator必然是一个Forward iteator
*/
/*  以advanced()为例
拿advance(）来说（这是许多算法内部常用的一个函数），该函数有两个 参数，迭代器p和数值n；
函数内部将p累进n次（前进n距离）。下面有三份定义，一份针对InputIterator,
一份针对BldirectionalIterator,另一份针对 RandomAcces lterator。
倒是没有针对Forward lterator而设计的版本，因为那和针对lnputtterator而设计的版本完全一致。
*/
template<class InputIteator,class Distance>
void advance_II(InputIteator& first,Distance n)
{
    //这个是求出前进n个之后的迭代器
    while(--n){
        first++;
    }
}
template<class BidrectionIteator,class Distance>
void advance_BI(BidrectionIteator& first,Distance n)
{
    if(n>0){
        while(--n){
        ++first;
         }
    }
    else{
        while(++n){
        --first;
         }
    }
}

template<class RandomAccessIteator,class Distance>
void advance_RAI(RandomAccessIteator& first,Distance n)
{
    i+=n;
}
/*
现在，当程序调用advance(）时，应该选用（调用）哪一份函数定义呢？如果选择advance_II()，
对RandomAccess Iterator而言极度缺乏效率，原本0(1) 的操作竟成为0(N)。如果选择advance_RAI(），
则它无法接受InputIterator。我们需要将三者合一，下面是一种做法：
*/
template<class InputIteator,class Distance>
void advance(InputIteator&i,Distance n){
    if(is_random_access_iterator(i)){
        advance_RAI(i,n);
    }
    else if(is_bidrectional_iterator(i)){
        advance_BI(i,n);
    }
    else{
        advance_II(i,n);
    }
}
/*
前述三个advance_xx(）都有两个函数参数，型别都未定（因为都是template参数）。
为了令其同名，形成重载函数，我们必须加上一个型别已确定的函数参数，使函数重载机制得以有效运作起来。

设计考虑如下：如果traits有能力萃取出迭代器的种类，我们便可利用这个
＂迭代器类型”相应型别作为advanced()的第三参数。这个相应型别一定必须
一个class type 不能只是数值号码类的东西，因为编译需依赖它（一个型别）
来进行重载决议（overloaded resolution） 

*/
//五个作为标记用的型别(tagtypes) 通过下方五种来进行重载决议  这里必须采用继承的方式
struct input_iterator_tag { }; 
struct output_iterator_tag{ }; 
struct forward_iterator_tag: public input_iterator_tag{ }; 
struct bidirectional_iterator_tag: public forward_iterator_tag{ } ; 
struct random_access_iterator_tag:public bidirectional_iterator_tag{ } ; 


template<class InputIteator,class Distance>
void advance_II(InputIteator& first,Distance n,input_iterator_tag)
{
    //这个是求出前进n个之后的迭代器
    while(--n){
        first++;
    }
}
template<class BidrectionIteator,class Distance>
void advance_BI(BidrectionIteator& first,Distance n,forward_iterator_tag)
{
    if(n>0){
        while(--n){
        ++first;
         }
    }
    else{
        while(++n){
        --first;
         }
    }
}

template<class RandomAccessIteator,class Distance>
void advance_RAI(RandomAccessIteator& first,Distance n,random_access_iterator_tag)
{
    i+=n;
}

/*
注意上述语法，每个—advance(）的最后一个参数都只声明型别，并未指定参数名称，
因为它纯粹只是用来激活重载机制，函数之中根本不使用该参数。如果硬要加上参数名称也可以，画蛇添足罢了。

行进至此，还需要个对外开放的上层控制接口，调用上述各个重载的 _advance ()。
这一上层接口只需两个参数，当它准备将工作转给上述的 _advance()时，才自行加上第三参数：迭代器类型。
因此，这个上层函数必须有能力从它所获得的迭代器中推导出其类型－这份工作自然是交给traits机制：
*/
template<class InputIteator,class Distance>
void advance(InputIteator& first,Distance n)
{
    _advance(i,n,iterator_traits<InputIteator>::iterator_category());
}
/*
注意上述语法，iterator_traits<Iterator>:：江erator_category(）将
产生一个暂时对象（道理就像int(）会产生一个int暂时对象一样），其型别应
一该隶属于前述五个迭代器类型之一。然后，根据这个型别，编译器才决定调用哪
个＿advance()重载函数。
*/