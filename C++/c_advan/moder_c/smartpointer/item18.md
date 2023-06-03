Item 18:对于独占资源使⽤std::unique_ptr
当你需要⼀个智能指针时， std::unique_ptr 通常是最合适的。可以合理假设，默认情况下， std::unique_ptr 等同于原始指针，而且对于⼤多数操作（包括取消引⽤），他们执⾏的指令完全相同。这意味着你甚⾄可以在内存和时间都⽐较紧张的情况下使⽤它。如果原始指针够小够快，那么 std::unique_ptr ⼀样可以。

std::unique_ptr体现了专有所有权语义。⼀个non-null  std::unique_ptr始终有其指向的内容。移动操作将所有权从源指针转移到⽬的指针，拷⻉操作是不允许的，因为如果你能拷⻉⼀个std::unique_ptr ，你会得到指向相同内容的两个 std::unique_ptr ，每个都认为⾃⼰拥有资源，销 毁时就会出现重复销毁。因此， std::unique_ptr 只⽀持移动操作。当 std::unique_ptr 销毁时，其 指向的资源也执⾏析构函数。而原始指针需要显⽰调⽤delete来销毁指针指向的资源。
确实原始指针不允许可以随便指，但是就不能复制自身来产生一个指针来指向不同的对象，这种现象就相当于move操作，所以原始指针相当于std::unique_ptr

但是也可以在所有权转移的场景中使⽤它，⽐如将⼯⼚返回的 std::unique_ptr 移⼊容器中，然后将容 器元素移⼊对象的数据成员中，然后对象随即被销毁。发⽣这种情况时，并且销毁该对象将导致销毁从 ⼯⼚返回的资源，对象 std::unique_ptr的数据成员也被销毁。如果所有权链由于异常或者其他⾮典型 控制流出现中断（⽐如提前return函数或者循环中的break），则拥有托管资源的 std::unique_ptr将保证指向内容的析构函数被调⽤，销毁对应资源。


auto delInvmt = [](Investment* pInvestment)
 {