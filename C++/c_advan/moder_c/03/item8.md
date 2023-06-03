//Item 8: Prefer nullptr to 0 and NULL.
你看这样对不对：字⾯值0是⼀个int不是指针。
如果C++发现在当前上下⽂只能使⽤指针，它会很不情愿的把0解释为指针，但是那是最后的退路。
⼀般来说C++的解析策略是把0看做int而不是指针。
实际上，NULL也是这样的。但在NULL的实现细节有些不确定因素，
因为实现被允许给NULL⼀个除了int之外的整型类型（⽐如long）。
这不常⻅，但也算不上问题所在。这⾥的问题不是NULL没有⼀个确定的类型，而是0和NULL都不是指针
类型。
在C++98中，对指针类型和整型进⾏重载意味着可能导致奇怪的事情。
如果给下⾯的重载函数传递0或NULL，它们绝不会调⽤指针版本的重载函数：

void f(int); //三个f的重载函数
void f(bool);
void f(void*);
f(0); //调⽤f(int)而不是f(void*)
f(NULL); //可能不会被编译，⼀般来说调⽤f(int),绝对不会调⽤f(void*)
//这里NULL底层时#define NULL 0   调⽤f(int)
nullptr的优点是它不是整型。
⽼实说它也不是⼀个指针类型，但是你可以把它认为是通⽤类型的指针。
nullptr的真正类型是std::nullptr_t，在⼀个完美的循环定义以后，std::nullptr_t⼜被定义为
nullptr。
std::nullptr_t可以转换为指向任何内置类型的指针，这也是为什么我把它叫做通⽤类型的指针。
使⽤nullptr调⽤f将会调⽤void*版本的重载函数，因为nullptr不能被视作任何整型：