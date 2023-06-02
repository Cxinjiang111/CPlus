#include"item4_1.h"
class Directory1{
public:
    Directory1();
};
Directory1::Directory1()
{
    std::size_t disks=tfs1.numDisks();
}
/*
现在，初始化次序的重要性显现出来了：除非tfs在tempDir之前先被初始化，否则tempDir的构造函数会用到尚未初始化的tfs。
但tfs和tempDir是不同的人 在不同的时间于不同的源码文件建立起来的， 它们是定义千不同编译单元内的 non-local static对象。
 如何能够确定tfs会在tempDir之前先被初始化？

喔，你无法确定 。再说一次，C++对“定义千不同的编译单元内的non-local static 对象” 的初始化相对次序并无明确定义。
这是有原因的：决定它们的初始化次序相 当困难，非常困难，根本无解。在其最常见形式，也就是多个编译单元内的non-local static对象经由 “模板隐式具现化，
implicit template instantiations” 形成（而后者自己可能也是经由 “模板隐式具现化” 形成）， 
不但不可能决定正确的初始化次序， 甚至往往不值得寻找 “可决定正确次序” 的特殊情况。

幸运的是一个小小的设计便可完全消除这个问题。 唯一需要做的是： 将每个 non-local static对象搬到自己的专属函数内（该对象在此函数内被声明为static)。
 这些函数返回一个reference指向它所含的对象。然后用户调用这些函数，而不直接 指涉这些对象。 换句话说， non-local static对象被local static对象替换了。
  Design Patterns迷哥迷姊们想必认出来了， 这是Singleton模式的一个常见实现手法。

个手法的基础在千：C++保证， 函数内的local static对象会在“ 该函数被调
用期间 ” “首次遇上该对象之定义式” 时被初始化。所以如果你以“函数调用 ＂（返
回 个reference指向local static对象）替换 “直接访问non-local static对象” ，
就获得了保证，保证你所获得的那个reference将指向一个历经初始化的对象。
更棒 的是， 如果你从未调用non-local static对象的 “仿真函数 ” ， 
就绝不会引发构造和析构成本；真正的non-local static对象可没这等便宜！
*/
class Directory{
public:
    Directory();
};
Directory::Directory()
{
    std::size_t disks=tfs().numDisks(); 
}
/*
这么修改之后，这个系统程序的客户完全像以前 一样地用它，唯一不同的是他们现在使用tfs(）和tempDir（）
而不再是tfs和tempDir。 也就是说他们使用函数 返回的 ” 指向static对象” 的references, 而不再使用static对象自身。

种结构下的reference-returning函数往往十分单纯： 第一行定义并初始化一 个local static对象，
第二行返回它。 这样的单纯性使它们成为绝佳的inlining候选人， 尤其如果它们被频繁调用的话（见条款30)。但是从另一个角度看， 这些函


数 内含static对象 ” 的事实使它们在多线程系统中带有不确定性。 再说一次， 任一
何 种non-const static 对象，不论它是local或non-local,在多线程环境下 “等待

某事发生” 都会有麻烦。 处理这个麻烦的一种做法是： 在程序的单线程启动阶段
(single-threaded startup portion)手工调用所有reference-returning函数，这可消除与初始化有关的 “竞速形势(race conditions) "。

当然啦， 运用reference-returning函数防止 “初始化次序问题” ， 前提是其中
有着一个对对象而言合理的初始化次序。如果你有一个系统，其中对象A必须在对 象B之前先初始化， 但A的初始化能否成功却又受制于B是否已初始化， 
这时候 你就有麻烦了。坦白说你自作自受。 只要避开如此病态的境况，此处描述的办法应该可以提供你良好的服务， 至少在单线程程序中。
既然这样，为避免在对象初始化之前过早地使用它们，你需要做三件事。第一， 手工初始化内置型non-member对象。
第二，使用成员初值列(member initialization lists)对付对象的所有成分。最后， 在 “初始化次序不确定性” 
（这对不同编译单 元所定义的non-local static对象是一种折磨）氛围下加强你的设计。
*/