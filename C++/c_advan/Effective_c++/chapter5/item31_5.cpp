class RealPerson: public Person { public: 
RealPe工son(const std::string& name, const Date& birthday, 
const Address& addr）
: theName(name), theBirthDate(birthday)， 七heAddress(add工） {} 
virtual ~RealPerson() { } std:: string name() const; std:: string birthDate () const; std: : string address () const;
private: 

std:: string theName; Date七heBirthDate; Address theAddress; 
};
//有了RealPerson之后， 写出Person::create就真的一点也不稀奇了：
std: :trl: :shared_ptr<Person> Person: :create(const std: :string& name, 
canst Date& birthday, const Address& addr) 
{
    return std::shared_ptr<Person>(new RealPerson(narne, birthday, 
}

/*
一个更现实的Person::create实现代码会创建不同类型的derived class对象， 取决千诸如额外参数值、 读自文件或数据库的数据、 环境变量等等。
Real Person示范实现Interface class的两个最常见机制之一：从Interface class (Person)继承接口规格， 然后实现出接口所覆盖的函数。Interface class 的第二 个实现法涉及多重继承， 那是条款40探索的主题。
Handle classes和Interface classes解除了接口和实现之间的耦合关系， 从而降 低文件间的编译依存性(compilation dependencies)。 如果你是犬儒学派（译注： 犬儒学派希望过一种符合自然的简朴生活，挨弃一切社会习俗和人为引导的种种欲 望）， 我知道你正等着我有义务给出的旁注。 “所有这些戏法得付出多少代价？ ” 你咕吹着。答案是计算器科学中通常需要付出的那些：它使你在运行期丧失若干速度， 又让你为每个对象超额付出若干内存。


在Handle classes身上，成员函数必须通过implementation pointer取得对象数 据。
 那会为每一次访问增加一层间接性。 而每一个对象消耗的内存数量必须增加 implementation ppinter的大小。
 最后，implementation pointer必须初始化（在Handle class构造函数内）， 指向一个动态分配得来的implementation object,
 所以你将蒙受因动态内存分配（及其后的释放动作）而来的额外开销，以及遭遇bad_alloc异常（内存不足）的可能性。

至于Interfaceclasses,巾十每个函数都是virtual,所以你必须为每次函数调用付出一个间接跳跃(indirectjump)成本（见条款7)。
此外Interfaceclass派生的 对象必须内含一个vptr(virtual table pointer,再次见条款7)，
这个指针可能会增加存放对象所盂的内存数量实际取决千这个对象除了Interfaceclass之外是否还有其他virtual函数来源。


最后， 不论Handle classes或Interface classes, 一旦脱离inline函数都无法有太大作为。 
条款30解释过为什么函数本体为r被inlined必须（很典型地）罚千头文件内， 
但Handle classes和Interface classes正是特别被设计用来隐藏实现细节如函数本体。
然而，如果只因为若干额外成本便不考虑Handleclasses和Interfaceclasses, 将是严重的错误。
Virtual函数不也带来成本吗？你并不会想要弃绝它们对不对？（如果是的话，那你读错书了。）
你应该考虑以渐进方式使用这些技术。在程序发展过程中使用Handleclasses和Interfaceclasses以求实现码有所变化时对其客户带 
来最小冲击。而当它们导致速度和／或大小差异过千重大以至千classes之间的耦合相形之下不成为关键时，
就以具象类(concreteclasses)替换日andleclasses和Interface classes。


*/
