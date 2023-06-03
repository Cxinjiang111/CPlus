
template<typename T>

struct __true_type{};
struct __false_type{};
template<class type>
struct __type_traits{
    typedef __true_type this_dummy_member_must_be_first;
    /*
不要移除这个成员。它通知”有能力自动将＿type＿traits特化”
的编译器说，我们现在所看到的这个＿type_traits template是特
殊的。这是为了确保万一编译器也使用一个名为＿type_traits而其
实与此处定义并无任何关联的template时，所有事情都仍将顺利运作

以下条件应被遵守，因为编译器有可能自动为各型别产生专属的＿＿type_traits 特化版本
－你可以重新排列以下的成员次序
－你可以移除以下任何成员
一绝对不可以将以下成员重新命名而却没有改变编译器中的对应名称 
－新加入的成员会被视为一般成员，除非你在编译器中加上适当支持
*/
    __type_traits<T>::has_trivial_default_constructor
    __type_traits<T>::has_trivial_copy_constructor
    __type_traits<T>::has_trivial_assignment_constructor
    __type_traits<T>::has_trivial_destructor
    __type_traits<T>::has_POD_type
};
/*
为什么SGI把所有内嵌型别都定义为—false_type呢？是的，SGI定义
出最保守的值，然后（稍后可见）再针对每一个标量型别(scalartypes)设计适当
的＿type_traits特化版本，这样就解决了问题。
上述＿type_traits可以接受任何型别的参数，五个typedefs将经由以下管道获得实值：

一般具现体(generalinstantiation)，内含对所有型别都必定有效的保守值。
上述各个has_trivial_xxx型别都被定义为＿false_type,就是对所有 型别都必定有效的保守值。

经过声明的特化版本，例如<type_traits.h>内对所有C+＋标量型别
(scalar types)提供了对应的特化声明。稍后展示

某些编译器（如SiliconGraphics N32和N64编译器）会自动为所有别别提 供适当的特化版本。（这真是了不起的技术。不过我对其精确程度存疑）
*/