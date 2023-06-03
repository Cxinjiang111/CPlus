/*
有时候你并不想继承baseclasses的所有函数，这是可以理解的。
在public继承下，这绝对不可能发生，因为它违反了public继承所暗不的“base和derivedclasses之间的is-a关系”。
（这也就是为什么上述using声明式被放在derivedclass的public区域的原因：
baseclass内的public名称在publiclyderived class内也应该是public。) 然而在private继承之下
（见条款39)它却可能是有意义的。例如假设Derived以 private形式继承Base,而Derived唯一想继承的rnfl是那个无参数版本。
using声 明式在这里派不上用场，因为using声明式会令继承而来的某给定名称之所有同名 函数在derivedclass中都可见。
不，我们需要不同的技术，即一个简单的转交函数
*/
class Base{
public:
    virtual void mf1();
    virtual void mf1(int);
};
class Derived:public Base{
public:
    Derived();
    virtual void mf1()
    {
        Base::mf1();//继承类中只想使用mf1()这种无参的函数
    }
    void mf4();
};
int main()
{   
    Derived d;
    int x;
    d.mf1();
    //d.mf1(2); error  

    return 0;
}
/*
inline转交函数(forwarding function)的另一个用途是为那些不支持using声明式（注：这并非正确行为）
的老旧编译器另辟一条新路， 将继承而得的名称汀入derived class作用域内。
这就是继承和名称遮掩的完整故事。但是当继承结合templates,我们又将面对 “继承名称被遮掩＂ 
的一个全然不同的形式。 关于 “ 以角括号定界” 的所有东西，详见条款43。


*/

