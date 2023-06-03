/*preder non-member non-friend functions to member function
宁可拿non-member non-friend函数替换member函数。 这样做可以增加封装件、 包裹弹性Cpackaging flexibility)和机能扩充性。
*/
class WebBrowser{
public:
    void clearCache();
    void clearHistory();
    void removeVookies();
};
//许多用户想到执行所有上述这些动作
//1.添加成员函数，
// class WebBrowser{
// public:
//     void clearEverything();
// };
//也可能由一个non-member函数调用适当的member函数提供
//2.外部提供接口函数
void clearBrowser(WebBrowser&wb){
    wb.clearCache();
    wb.clearHistory();
    wb.removeVookies();
}
/*
面向对象守则要求，数据以及操作数据的那些函数应该被捆绑在一块，这意味它
建议member函数是较好的选择。不幸的是这个建议不正确。这是基千对面向对象真实意义的一个误解。
面向对象守则要求数据应该尽可能被封装，然而与直观相反地， 
member函数clearEverything带来的封装性比non-member函数clearBrowser低。 
此外，提供non-member函数可允许对WebBrowser相关机能有较大的包裹弹性
(packaging flexibility), 而那最终导致较低的编译相依度，增加WebBrowser的可延伸性。 
因此在许多方面non-member做法比member做法好。重要的是，我们必须了解其原因。

让我们从封装开始讨论。 如果某些东西被封装， 它就不再可见。 
愈多东西被封装， 愈少人可以看到它。 而愈少人看到它， 我们就有愈大的弹性去变化它， 因为我们的改
变仅仅直接影响看到改变的那些人事物。 因此， 愈多东西被封装， 我们改变那些东西 的能力也就愈大。
 这就是我们首先推崇封装的原因： 它使我们能够改变事物而只影响有限客户。
现在考虑对象内的数据。 愈少代码可以看到数据（也就是访问它）， 愈多的数据 可被封装， 
而我们也就愈能自由地改变对象数据， 例如改变成员变量的数量、 类型等 等。 
如何量测 “有多少代码可以看到某一块数据” 呢？我们计算能够访问该数据的函 数数量， 作为一种粗糙的量测。
 愈多函数可访问它， 数据的封装性就愈低。


条款22曾说过，成员变量应该是private,因为如果它们不是，就有无限量的函数
可以访问它们， 它们也就毫无封装性。 能够访问private成员变量的函数只有class的member函数加上friend函数而已。
如果要你在一个member函数（它不只可以访问class内的private数据，也可以取用private函数、enums、typedefs等等）
和一个non-member, non-friend函数（它无法访问上述任何东西）之间做抉择， 而且两者提供相同机能， 
那么， 导致较大封装性的是non-member non-friend函数， 因为它并不增加“ 能够访问 class内之private成分＂的函数数量。
这 就解释了为什么clearBrowser（一个non-member non-friend函数）比clearEverything（一个member函数）更受欢迎的原因：
 它导致WebBrowser class有较大的封装性。

在这一点上有两件事情值得注意。第一，这个论述只适用千non-membernon-friend函数 。 
friends 函数对class private成员的访问权力和member函数相同， 因此两者对封 装的冲击力道也相同。
从封装的角度看，这里的选择关键并不在member和non-member函数之间， 而是在member和non-member non-friend函数之间。
（当然，封装并非唯一考虑。条款24解释当我们考虑隐式类型转换，应该在member和non-member函数之间抉择。） 


第二件值得注意的事情是，只因在意封装性而让函数”成为class的non-member",“并不 意味它 不可以是另一个class的member"。
这对那些习惯千 ” 所有函数都必须定义于class内 ” 的语言（如Eiffel, Java, C#)的程序员而言， 可能是个温暖的慰藉。
例如我们可以令clearBrowser成为某工具类(utility cla ss)的一个static member函数。
只要它不是WebBrowser的一部分（或成为其friend)，就不会影响WebBrowser的private 成员封装性。
*/
namespace WebBrowserStuff{
    class WebBrowser{};
    void clearBrowser(WebBrowser &wb);
};
/*
然而这不只是为了看起来自然而已。 要知道， namespace和classes不同， 前者可 跨越多个源码文件而后者不能。
这很重要， 因为像clearBrowser这样的函数是个 “ 提供便利的函数” ，如果它既不是members也不是friends, 
就没有对WebBrowser的特殊访问权力， 也就不能提供 “ WebBrowser客户无法以其他方式取得 ” 的机能。 
举个例 子， 如果clearBrowser不存在，客户端就只好自行调用clearCache, clearHistory 和removeCookies。

一个像WebBrowser这样的class可能拥有大量便利函数，某些与书签(bookmarks)
有关，某些与打印有关，还有 一 些与cookie的管理有关……通常大多数客户只对其中
某些感兴趣。 没道理一个只对书签相关便利函数感兴趣的客户却与……呃...…例如
个cookie相关便利函数发生编译相依关系。分离它们的最直接做法就是将书签相关便 利函数声明千一个头文件，
将cookie相关便利函数声明于另一个头文件，再将打印相 关便利函数声明千第三个头文件，依此类推：
*/
//头文件，webbrowser.h 这个头文件针对class WebBrowser自身及WebBrowser核心机能
namespace WebBrowserStuff{
    class WebBrowser{};
    void clearBrowser(WebBrowser &wb);
};
////头文件，webbrowserbookmarks.h
namespace webbrowserbookmarks
{

}
////头文件，webbrowsercookies.h
namespace webbrowsercookies
{
    
}
/*
注意，这正是C丑标准程序库的组织方式。标准程序库并不是拥有单 、整体、庞大的<c++s七andardLibrary>头文件并在其中内含std命名空间内的每一样东西，
 而是有数十个头文件(<vector>,<algori thrn>,<rnemory>等等），每个头文件声明std 的某些机能。如果客户只想使用vector相关机能，
 他不需要include<rnemory>; 如果客户不想使用list,也不需要扣nclude <list>。这允许客户只对他们所用的那一小部分系统形成编译相依
 （见条款31,其中讨论降低编译依存性的其他做法）。以 此种方式切割机能并不适用于class成员函数，因为一个class必须整体定义，不能被 分割为片片段段。
*/
/*
将所有便利函数放在多个头文件内但隶属同一个命名空间，意味客户可以轻松扩展这一组便利函数。
他们需要做的就是添加更多non-member non-friend函数到此命名
空间内。举个例子，如果某个WebBrowser客户决定写些与影像下载相关的便利函数，
他只需要在WebBrowserStuff命名空间内建立一个头文件，内含那些函数的声明即可。
新函数就像其他旧有的便利函数那样可用且整合为一体。这是class无法提供的另一
个性质， 因为 class定义式对客户而言是不能扩展的。 当然啦， 客户可以派生出新的classes,
 但derived classes无法访问base class中被封装的（即private)成员， 丁是如此的 ＂扩展机能＂ 拥有的只是次级身份。 
 此外一如条款7所说， 并非所有classes都被 设计用来作为 base classes。

*/