区分通⽤引⽤与右值引⽤
据说，真相使⼈⾃由，然而在特定的环境下，⼀个精⼼挑选的谎⾔也同样使⼈解放。这⼀节就是这样⼀
个谎⾔。因为我们在和软件打交道，然而，让我们避开“谎⾔(lie)”这个词，不妨说，本节包含了⼀种“抽象(abstraction)”。
住：
如果⼀个函数模板参数的类型为T&&，并且T需要被推导得知，或者如果⼀个对象被声明为
auto&&，这个参数或者对象就是⼀个通⽤引⽤。
如果类型声明的形式不是标准的type&&，或者如果类型推导没有发⽣，那么type&&代表⼀个右
值引⽤。
通⽤引⽤，如果它被右值初始化，就会对应地成为右值引⽤;如果它被左值初始化，就会成为左值引
⽤