为了了解std::move和std::forward，⼀种有⽤的⽅式是从它们不做什么这个⻆度来了解它们。
std::move不移动(move)任何东西，std::forward也不转发(forward)任何东西。在运⾏期间(runtime)，
它们不做任何事情。它们不产⽣任何可执⾏代码，⼀字节也没有。

std::move和std::forward仅仅是执⾏转换(cast)的函数（事实上是函数模板）。std::move⽆条件
的将它的参数转换为右值，而std::forward只在特定情况满⾜时下进⾏转换。
它们就是如此。这样的解释带来了⼀些新的问题，但是从根本上而⾔，这就是全部内容。
在logAndProcess函数的内部，参数param被传递给函数process。函数process分别对左值和右值
参数做了重载。当我们使⽤左值来调⽤logAndProcess时，⾃然我们期望该左值被当作左值转发给
process函数，而当我们使⽤右值来调⽤logAndProcess函数时，我们期望process函数的右值重载
版本被调⽤。
但是参数param，正如所有的其他函数参数⼀样，是⼀个左值。每次在函数logAndProcess内部对函
数process的调⽤，都会因此调⽤函数process的左值重载版本。为防如此，我们需要⼀种机制
(mechanism) : 当且仅当传递给函数logAndProcess的⽤以初始化参数param的值是⼀个右值时，参
数param会被转换为有⼀个右值。这就是为什么std::forward是⼀个有条件的转换：它只把由右值初
始化的参数，转换为右值。
你也许会想知道std::forward是怎么知道它的参数是否是被⼀个右值初始化的。举个例⼦，在上述代
码中，std::forward是怎么分辨参数param是被⼀个左值还是右值初始化的？ 简短的说，该信息藏在
函数logAndProcess的模板参数T中。该参数被传递给了函数std::forward，它解开了含在其中的信
息。该机制⼯作的细节可以查询 Item 28.
考虑到std::move和std::forward都可以归结于转换，他们唯⼀的区别就是std::move总是执⾏转
换，而std::forward偶尔为之。你可能会问是否我们可以免于使⽤std::move而在任何地⽅只使⽤
std::forward。 从纯技术的⻆度，答案是yes: std::forward是可以完全胜任，std::move并⾮必
须。当然，其实两者中没有哪⼀个函数是真的必须的，因为我们可以到处直接写转换代码，但是我希望
我们能同意：这将相当的，嗯，让⼈恶⼼。
std::move的吸引⼒在于它的便利性： 减少了出错的可能性，增加了代码的清晰程度。考虑⼀个类，我
们希望统计有多少次移动构造函数被调⽤了。我们只需要⼀个静态的计数器(static counter)，它会在移
动构造的时候⾃增。假设在这个类中，唯⼀⼀个⾮静态的数据成员是std::string，⼀种经典的移动构
造函数（例如，使⽤std::move)可以被实现如下: