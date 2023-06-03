/*了解new和delete的合理替换时机*/

/*
用来检测运用上的错误。如果将“new所得内存“delete掉却不幸失败，会导 
致内存泄漏(memoryleaks)。如果在“new所得内存“身上多次delete则会 
导致不确定行为。如果operatornew持有一串动态分配所得地址，而operator 
delete将地址从中移走，倒是很容易检测出上述错误用法。此外各式各样的编 
程错误可能导致数据“overruns"（写入点在分配区块尾端之后）或“underruns" 
（写入点在分配区块起点之前）。如果我们自行定义一个operatornews,便 
可超额分配内存，以额外空间（位千客户所得区块之前或后）放置特定的byte patterns
（即签名，signatures)。operatordeletes便得以检查上述签名是否原 封不动，
若否就表示在分配区的某个生命时间点发生了overrun或underrun,这 
时候operatordelete可以志记Clog)那个事实以及那个惹是生非的指针。

为了强化效能。 编译器所带的 operator new和operator delete主要用于一 
般目的，它们不但可被长时间执行的程序（例如网页服务器，web servers)接受，
也可被执行时间少千一秒的程序接受。 它们必须处理一系列需求， 包括大块内 
存、 小块内存、 大小混合型内存。 它们必须接纳各种分配形态， 范围从程序存
活期间的少量区块动态分配， 到大数量短命对象的持续分配和归还。 它们必须考虑破碎问题(fragmentation)，
这最终会导致程序尤法满足人区块内存要求， 即使彼时有总量足够但分散为许多小区块的自由内存。

为了收集使用上的统计数据。 在一头栽进定制型news和定制型deletes之前， 理当先收集你的软件如何使用其动态内存。
分配区块的大小分布如何？寿命分 布如何？它们倾向千以FIFO（先进先出）次序或LIFO（后进先出）
次序或随机次序来分配和归还？它们的运用型态是否随时间改变， 也就是说你的软件在 
不同的执行阶段有不同的分配／归还形态吗？任何时刻所使用的最大动态分配量 （高水位）是多少？
自行定义operator new和operator delete使我们得以 轻松收集到这些信息。
*/
#include<iostream>
#include<exception>
static const int signature=0xABCDEF;
typedef unsigned char Byte;
void *operator new(std::size_t size) throw(std::bad_alloc)
{
    using namespace std;
    size_t realSize=size+2*sizeof(int);//实际的分配的内存的大小
    void *pMem=malloc(realSize);
    //将signature写入内存的最前段落和最后段落
    //分配内存存在越界的情况的标签判断
    *(static_cast<int*>(pMem))=signature;
    *(reinterpret_cast<int*>(static_cast<Byte*>(pMem)+realSize-sizeof(int)))=signature;
    return static_cast<Byte*>(pMem)+sizeof(int);

}

/*
为了增加分配和归还的速度。泛用型分配器往往（虽然并不总是）比定制型分 配器慢，
特别是当定制型分配器专门针对某特定类型之对象而设计时。Class专 属分配器是“区块尺寸固定”之分配器实例，
例如Boost提供的Pool程序库便 是。如果你的程序是个单线程程序，但你的编译器所带的内存管理器具备线程 安全，
你或许可以写个不具线程安全的分配器而大幅改善速度。当然，在获得 "operator new和operatordelete有加快程序速度的价值”这个结论之前，
首先请分析你的程序，确认程序瓶颈的确发生在那些内存函数身上。

为了降低缺省内存管理器带来的空间额外开销。泛用型内存管理器往往（虽然 并非总是）不只比定制型慢，
它们往往还使用更多内存，那是因为它们常常在一每个分配区块身上招引某些额外开销。
针对小型对象而开发的分配器（例如 Boost的Pool程序库）本质上消除了这样的额外开销。

·为了弥补缺省分配器中的非最佳齐位(suboptimalalignment)。一如先前所说， 
在x86体系结构上doubles的访问最是快速一一如果它们都是8-byte齐位。但是编译器自带的operatornews并不保证对动态分配而得的doubles采取
8-	byte齐位。这种情况下，将缺省的operatornew替换为一个8-byte齐位保证版，可导致程序效率大幅提升。

为了将相关对象成簇集中。如果你知道特定之某个数据结构往往被一起使用，而你又希望在处理这些数据时将“内存页错误"(pagefaults)的频率降至最低，
那么为此数据结构创建另一个heap就有意义，这么一来它们就可以被成簇集中 在尽可能少的内存页(pages)上。new和delete的“placement版本”
（见条 款52)有可能完成这样的集簇行为。

为了获得非传统的行为。有时候你会希望operatorsnew和delete做编译器附 带版没做的某些事情。
例如你可能会希望分配和归还共享内存(sharedmemory)内的区块，但唯一能够管理该内存的只有CAPI函数，那么写下一个定制版new 和delete
（很可能是placement版本，见条款52)，你便得以为CAPI穿上一件C+＋外套。你也可以写一个自定的operatordelete,在其中将所有归还内 
存内容覆盖为o,藉此增加应用程序的数据安全性。


*/



