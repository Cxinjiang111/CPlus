/*
看起来不错。 但是有个隐晦的陷阱： 并不是所有迭代器都是class type。 原生
指针就不是！如果不是class type, 就无法为它定义内嵌型别。 但STI.,（以及整个泛
一
型思维）绝对必须接受原生指针作为 种迭代器，所以上面这样还不够。有没有办法
可以让上述的一般化概念针对特定情况（例如针对原生指针）做特殊化处理呢？
是的，template partial specialization可以做到。
是的，template partial specialization可以做到。
Partial Specialization（偏特化）的意义
大致的意义是： 如果class template拥有 个以上的 template参数， 我们可以针对其中某个（或数个， 但非全部）template参数进行特
化工作。换句话说，我们可以在泛化设计中提供一个特化版本（也就是将泛化版本 中的某些template参数赋予明确的指定）。

*/
//假设有一个classtemplate如下：
template<typename U, typename V, typename T> 
class C {

 }; 
 /*
 partial specialization的字面意义容易误导我们以为，所谓“偏特化版”一定
 是对template参数u或v或T（或某种组合）指定某个参数值。其实不然，［Austern99] 对于partialspecialization的意义说得十分得体：”所谓partialspecialization的 意思是提供另一份template定义式，而其本身仍为templatized"。《泛型思维》 一书对partialspecialization的定义是：“针对（任何）template参数更进—步的条
件限制所设计出来的一个特化版本”。由此，面对以下这么一个classtemplate: 
 
 */
template<typename T>
class C{

};
//特化版
template<typename T>
class C1<T*> {//这个特化版本仅适用于“T为原生指针＂的情况
//"T为原生指针”便是“T为任何型别”的一个更进一步的条件限制
};
//有了这项利器，我们便可以解决前述“内嵌型别“未能解决的问题。先前的
//问题是，原生指针并非class,因此无法为它们定义内嵌型别。现在，我们可以针
//对“迭代器之template参数为指针”者，设计特化版的迭代器。
//提高警觉，我们进入关键地带了！下面这个classtemplate专门用来“萃取“ 迭代器的特性，而valuetype正是迭代器的特性之一：
template<class I>
struct iterator_traits{
    typedef typename I::value_type;
};
/*
这个所谓的traits,其意义是，如果I定义有自己的valuetype,那么通过这个traits的作用，
萃取出来的value_type就是I::value＿type。换句话说， 
如果工定义有自己的valuetype,先前那个func(）可以改写成这样：
*/
template<class I>
typename iterator_traits<I>::value_type //找I下的 value_type 这个value_type是之前提供好的
func(I iter){
    return *iter;
}
//但这除了多一层间接性，又带来什么好处呢？好处是traits可以拥有特化版
//本。现在，我们令·iterator七rai七es拥有一入r-partial specializations如下：
template<class T>
struct iterator_traits<T*>{
    typedef T value_type;
};


/*vector 中的萃取
typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
rebind<_Tp>::other _Tp_alloc_type;
typedef typename __gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer pointer;

*/
//STL中最常用的五种迭代器value type ;different type ;pointer;iterator_catagoly
template<typename I>
struct iterator_traits{
    typedef typename I::iterator catagoly;
    typedef typename I::value_type;
    typedef typename I::different_type;
    typedef typename I::pointer;
    typedef typename I::reference ;



};

