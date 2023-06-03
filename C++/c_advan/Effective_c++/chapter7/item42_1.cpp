/*
嵌套从属名称有可能导致解析(parsing)困难。举个例子，假设我们令print2nd更愚蠢些，这样起头：
*/
template<typename C>
void print2nd(const C&container)
{
    C::const_iterator *x;//const_iterator有可能是个成员 不是类型这时就会出问题
}
/*
看起来好像我们声明 x为 一 个local变量，它是个指针， 指向 一个 C::const_iterator。 
但它之所以被那么认为， 只因为我们 ” 已经知道 ” C::const_iterator是个类型。
如果C::const_iterator不是个类型呢？如果c有个static成员变量而碰巧被命名为const_iterator, 
或如果x碰巧是个global变量名称呢？那样的话上述代码就不再是声明一个local变量，而是一个相乘动作：
 C: :const_iterator乘以x。当然啦，这听起来有点疯狂，但却是可能的，而撰写C++解析器的人必须
 操心所有可能的输入， 甚至是这么疯狂的输入。

在我们知迫c是什么之前，没有任何办法可以知道C::const_iterator是否为
个类型。而当编译器开始解析template print2nd时， 尚未确知c是什么东西。
C++有个规则可以解析(resolve)此一歧义状态：如果解析器在template中遭遇－
个嵌套从属名称， 它便假设这名称不是个类型，除非你告诉它是。所以缺省情况下嵌套从属名称不是类型。
此规则有个例外， 稍后我会提到。
*/
template<typename C>
void print2nd(const C&container)
{
    if(container.size()>=2)
    {
        C::const_itertor iter(container.begin());//这个并没有做到显式让编译器知道，而是让他去自动识别 这就有可能出错
    }
}
/*
现在应该很沾楚为什么这不是有效的C++代码了吧。iter声明式只有在C::const_iterator是个类型时才合理，
但我们并没有告诉C++说它是，于是C++假设它不是。若要矫正这个形势，我们必须告诉C++说C::canst_iterator是个类型。
只要紧临它之前放置关键字typename即可：


*/
template<typename C>
void print2nd(const C&container)
{
    if(container.size()>=2)
    {
       typename C::const_itertor iter(container.begin());//这个显式让编译器知道，而是让他去自动识别出其他的非法问题，
       //相当于限定它就是一个类型，编译器也必须往类型上去识别，不是类型直接报错，
    }
}

/*
－般性规则很简单：任何时候当你想要在template中指涉个嵌套从属类犁名称， 就必须在紧临它的前一个位置放上关键字typenarne。 
（再提醒一次，很快我会谈到一个例外。 ）
typenarne只被用来验明<嵌套>从属类型名称；其他名称个该有它存在。例如下面这个function template,接受一个容器和一个”指向该容器”的迭代器：
*/ 
template<typename C>
void f(const C&container,//不允许使用typename 
        typename C::iterator iter);//一定要使用typename。 iterator是个从属名称对象中的类型非template
/*
上述的C并不是嵌套从属类型名称（它并非嵌套于任何“取决于template参数”的东西内），所以声明container时并不需要以typename为前导，
但C::iterator是个嵌套从属类型名称，所以必须以typename为前导。
*/