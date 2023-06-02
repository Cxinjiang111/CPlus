/*编译器默默编写并调用那些函数
编译器产生的析构函数是个non-virtual 
copy构造函数和copy assignment操作符，编译器创建的版本只是单纯的将来源对象
的每一个non-static成员变量拷贝到目标对象
*/
#include<string>
#include<iostream>
using namespace std;
template<typename T>
class NameObject{
public:
    NameObject(const char *name,const T&value)
    {
        cout<<" char *"<<endl;
    }
    NameObject(const std::string&name,const T&value)
    {
        cout<<"std::string"<<endl;
    }
private:
    std::string nameValue;
    T objectValue;

};
/*
由千其中声明了一个构造函数，编译器千是不再为它创建default构造函数。
这很重要，意味如果你用心设计一个class,其构造函数要求实参，
你就无须担心编译器会毫无挂虑地为你添加一个无实参构造函数（即default构造函数）而遮盖掉你的 版本。
*/
int main()
{
NameObject no1("okkokok",2);// char *
NameObject no2(no1);
}
/*
编译器生成的copy构造函数必须以nol.nameValue和nol.objectValue为初值 设定no2.nameValue和no2.objectValue。
两者之中，nameValue的类型是string,而标准string有个copy构造函数，
 所以no2.nameValue的初始化方式是调用string的copy构造函数并以nol.nameValue为实参。 
 另 一 个成员NamedObject<int>::objectValue的类型是int（因为对此template具现体而言T 是int)，
  那是个内置类型， 所以no2.objectValue会以“拷贝nol.objectValue 内的每一 个bits"来完成初始化。
编译器为NamedObject<int>所生的copy assignment操作符， 其行为基本上与 copy构造函数如出一辙，
 但一般而言只有当生出的代码合法且有适当机会证明它有 意义（见下页）， 其表现才会如我先前所说。
  万一两个条件有一 个不符合， 编译器 会拒绝为class生出operator= 。
*/