/*
然而，让我们把它放在一旁，佯装changeBackground的确提供了强烈保证（我有信心你可以想出个什么办法顺利过渡，
或许你可以改变它的参数类型，从istream 改为一个内含图像数据的文件名称）。
有个一般化的设计策略很典型地会导致强烈 保证， 很值得熟悉它。这个策略被称为copy and swap。 
原则很简单： 为你打算修改的对象（原件）做出一份副本，然后在那副本身上做一切必要修改。 
若有任何修改动作抛出异常， 原对象仍保持未改变状态。待所有改变都成功后， 再将修改过的
那个副本和原对象在一个不抛出异常的操作中置换(swap)。

实现上通常是将所有 “隶属对象的数据 “ 从原对象放进另一个对象内，然后赋予原对象一个指针，
指向那个所谓的实现对象(implementation object, 即副本）。 这种手法常被称为pimpl idiom,
条款31详细描述了它。对PrettyMenu而言，典型写法如下：
*/
#include<memory>
#include<mutex>
class Image{

};
class Lock{
public:
    Lock(std::mutex m1):m2(std::move(m1)){};
private:
    std::mutex m2;
};
struct PMImpl{
    std::shared_ptr<Image> bgImage;
    int imageChanges;
};
class PrettyMenu{
public:
    void chageBackground(std::istream&imaSrc);
private:
    std::mutex m1;
    std::shared_ptr<PMImpl> pImpl;
};
void PrettyMenu::chageBackground(std::istream&imaSrc)
{
    using std::swap;
    Lock m1(&m);
    std::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));//临时的副本
    pNew->bgImage.reset(new Image(imgsrc));//修改副本
    ++pNew->imageChanges;//无异常，++；
    swap(pNew,pImpl);//交换副本和本体
}
/*
此例之中我选择让PMimpl成为一个struct而不是一个class, 这是因为
PrettyMenu的数据封装性已经由于“ plmpl是private'而获得了保证。如果令PMimpl
为 个class, 虽然 样好，有时候却不太方便（但也保持了面向对象纯度）。如果
“你要， 也可以将PMimpl嵌套于PrettyMenu内，但打包问题(packaging,例如独
立撰写异常安全码” )是我们这里所挂虑的事。

*/
/*
copy-and-swap"策略是对对象状态做出 “全有或全无” 改变的一个很好办法，
但一般它井不保证整个函数有强烈的异常安全性。为了解原因， 让我们考虑
changeBackground的一个抽象概念：someFunc。它使用copy-and-swap策略，
但函数内还包括对另外两个函数fl和f2的调用：
void someFunc()
{
    ...//对local状态做一份副本
    f1();
    f2();
     ...   //修改后的状态置换过来 
     //好奇的是为啥f1 f2函数不在修改后并才执行呢
}
显然， 如果fl或f2的异常安全性比 “强烈保证“ 低， 就很难让sorneFunc 
成为“强烈异常安全＇。举个例子，假设fl只提供基本保证，那么为了让sorneFunc 
提供强烈保证，我们必须写出代码获得调用 fl之前的整个程序状态、捕捉fl的所有可能异常、 然后恢复原状态。
如果fl和f2都是 “强烈异常安全” ，情况并不就此好转。 毕竟如果fl圆满结束， 
程序状态在仔何方面都可能有所改变， 因此如果f2随后抛出异常，程序状态和sorneFunc被调用前并不相同，
甚至当f2没有改变任何东西时也是如此。

问题出在 “ 连带影响” (sideeffects)。如果函数只操作局部性状态Clocal state,
例如sorneFunc只影响其 “ 调用者对象” 的状态）， 便相对容易地提供强烈保证。 
但是当函数对 “非局部性数据“ (non-local data)有连带影响时，提供强烈保证就困难得多。 
举个例子， 如果调用fl带来的影响是某个数据库被改动了， 那就很难 让sorneFunc具备强烈安全性。
一般而言在 “ 数据库修改动作“ 送出之后， 没有什么做法可以取消并恢复数据库旧观，
因为数据库的其他客户可能已经看到了这一笔新数据。


这些议题想必会阻止你为函数提供强烈保证一􀃆即使你想那么做。另一个主题
是效率。copy-and-swap的关键在千 “修改对象数据的副本， 然后在一个不抛异常
的函数中将修改后的数据和原件置换” ，因此必须为每一个即将被改动的对象做出 一
个副本， 那得耗用你可能无法（或无意愿）供应的时间和空间。 是的， 大家都希
望提供 “强烈保证” ；当它可被实现时你的确应该提供它， 但 “强烈保证 ” 并非在
任何时刻都显得实际。

当”强烈保证“切实际时，你就必须提供 “基本保证” 。现实中你或许会发
现，你可以为某些函数提供强烈保证，但效率和复杂度带来的成本会使它对许多人而言摇摇欲坠。 
只要你曾经付出适当的心力试图提供强烈保证， 万一实际不可行， 使你退而求其次地只提供基本保证，
任何人都不该因此责难你。 对许多函数而言，”异常安全性之某本保证” 是－个绝对通情达理的选择。

如果你写的函数完全不提供异常安全保证，情况又有点不同。 因为他人可以合 理假设
你在这方面有缺失，直到你证明自己的清白。是的，你应当写出异常安全码。 
个过你也可能有令人信服的理巾。 再次考虑先前出现的那份调用函数fl和f2的someFunc实现代码。
假设f2完全没有提供异常安全保证，甚至连基本保证都没有， 那便意味一旦f2抛出异常，
程序有可能在f2内泄漏资源。 这意味f2可能败坏数 据结构， 
例如带序数组(sorted arrays)可能不再处千排序状态下、
从某数据结构搬移至另一数据结构的对象有可能遗失……等等。someFunc没办法补偿那些问题。
如果someFunc调用的函数没有提供任何异常安全保证，someFunc自身也不可能提供任何保证。
*/

