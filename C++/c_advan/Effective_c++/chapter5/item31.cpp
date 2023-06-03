/*将文件间的编译依存关系降至最低

·	支持 “编译依存性最小化” 的 般构想是： 相依于声明式， 不要相依千定义式。 基于此构想的两个手段是Handle classes和Interface classes。
·	程序库头文件应该以 “ 完全且仅有声明式” (full and declaration-only forms)的 形式存在。 这种做法不论是否涉及templates都适用。


*/
/*
假设你对C丑程序的某个class实现文件做了些轻微修改。注意，修改的不是 class接口，
而是实现， 而且只改private成分。 然后重新建置这个程序， 并预计只花数秒就好。
毕竟只有一个class被修改。 你按下 “Build"按钮或键入make（或其他类似命令）， 
然后大吃一惊， 然后感到窘困， 因为你意识到整个世界都被重新编译和连接了！
当这种事情发生， 难道你不气恼吗？

问题出在C+＋并没有把 “将接口从实现中分离” 这事做得很好。
Class的定义式不只详细叙述了class接口， 还包括十足的实现细目。 例如：
*/
#include<string>
class Date{};
class Address{};
class Person{
public:
    Person(const std::string&name,const Date&birthday,
            const Address &addr);
    std::string name()const;
    std::string bithDate()const;
    std::string address()const;

private:
    std::string theName;
    Date theBirthDate;
    Address theAddress;
};
/*
这里的class Person无法通过编译一一如果编译器没有取得其实现代码所用到 
的classes string, Date和Address的定义式。这样的定义式通常由＃include指示符提供， 
所以Person定义文件的最上方很可能存在这样的东西：
#include <string> 
#include "date.h" 
#include "address.h"
不幸的是， 这么一来便是在Person定义文件和其含入文件之间形成了一种编 译依存关系(compilationdependency)。 
如果这些头文件中有任何一个被改变， 或 这些头文件所倚赖的其他头文件有任何改变，
那么每一个含入Personclass的文件 就得重新编译， 任何使用Personclass的文件也必须重新编译。
这样的连串编译依 存关系(cascadingcompilation dependencies)会对许多项目造成难以形容的灾难。
*/