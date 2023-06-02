
/*
隐式转换
*/
class FontHandle{};
//Font类主要设计目的就是为了防止资源泄漏
class Font{
public:
    Font();
    explicit Font(FontHandle fh):f(fh){};//获取资源 采用值传递的方法
    ~Font(){releaseFont(f);}//释放资源
    FontHandle get(){return f;} //这样就从Font转换为FontHandle类型 显式转换 也行，就是需要 
private:
    FontHandle f;//原始资源
};
FontHandle getFont()
{
    Font p;
    return p.get();
}
void releaseFont(FontHandle fh);
int main()
{
    Font *p=new Font();
    FontHandle *ph=&(p->get());//实现了FOnt-->FontHandle
    //这样隐式转换会增加错误发生机会，
    Font f1(getFont());
    FontHandle f2=f1;//原意是要拷贝一个Font对象，
    //却反而将f1隐式转换为其底部的FontHandle 然后才复制它

    //以上程序有个FontHandle由Font对象f1管理，但那个FontHandle也可以通过
    //直接 使用f2取得.当f1被销毁时，字体会被释放，而f2因此成为虚吊的
}
/*
是否该提供一个显式转换闭数（例如get成员函数）将RAIiclass转换为其底
部资源， 或是应该提供隐式转换， 答案主要取决千RAIiclass被设计执行的特定工
“
作， 以及它被使用的情况。 最佳设计很可能是坚持条款18的忠告： 让接口容易 被正确使用， 不易被误用 “ 。
通常显式转换函数如get是比较受欢迎的路子， 因为
它将 “非故意之类型转换” 的可能性最小化了。 然而有时候， 隐式类型转换所带来的自然用法” 也会引发天秤倾斜。
你的内心也可能认为，RAII class内的那个返回原始资源的函数， 与 “ 封装” 发生矛盾。 
那是真的， 但一般而言它谈不上是什么设计灾难。RAIi classes并不是 为了封装某物而存在；
它们的存在是为了确保一个特殊行为一资源释放一一会发 生。如果一定要，当然也可以在这基本功能之上再加层资源封装，但那并非必要。
 此外也有某些RAIi classes结合十分松散的底层资源封装， 藉以获得真正的封装实现。
 例如trl: :shared_ptr将它的所有引用计数机构封装了起来，但还是让外界很 容易访问其所内含的原始指针。
 就像多数设计良好的classes 一样，它隐藏了客户不 需要看的部分， 但备妥客户需要的所有东西。
*/
