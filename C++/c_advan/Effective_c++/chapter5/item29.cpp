/*为异常安全而努力是值得
异常安全函数(Exception-safe functions)即使发生异常也个会泄漏资源或允许
任何数据结构败坏。这样的函数区分为三种可能的保证：基本型、强烈型、不抛异常型。

“强烈保证 ” 往往能够以copy-and-swap实现出来，但 “强烈保证” 并非对所
有函数都可实现或具备现实意义。

函数提供的 “异常安全保证“ 通常最高只等千其所调用之各个函数的 “异常安 
全保证” 中的最弱者。
*/
#include<mutex>
class Image{

};
class PrettyMenu{
public:
    void changeBackground(std::istream&imgSrc);//改变背景图像
private:
    std::mutex m;//互斥器
    Image *bgImage;//背景的图像
    int imageChanges;//背景图像被改变的次数
};
void PrettyMenu::changeBackground(std::istream&imgSrc)
{
    m.lock();                   // 取得互斥器
    delete bgImage;             //拜托旧的背景图像
    ++imageChanges;             //修改图像变更次数
    bgImage =new Image(imgSrc);//安装新的背景图像
    m.unlock();                 //释放互斥器
}
/*异常安全有两个条件 这个函数居然没有满足一个？？？
当异常被抛出时，带有异常安全性的函数会：
不泄露任何资源： 上述代码没有做到这点，因为一旦new Image(imgSrc)导致异常
    对unlock的调用就绝不会执行，于是互斥器就永远被把持住了
不允许数据败坏：如果new Image(imgSrc)抛出异常，bgimage就是指向一个被
删除的对象，imageChanges已被累加，而其实并没有新的图像被成功安装，
*/
//方法如下 Lock资源管理类
class Lock{
public:
    Lock(std::mutex& m1){};
private:
    std::mutex m2;
};
void PrettyMenu::changeBackground(std::istream&imgSrc)
{
    //这个Lock类的作用域就是{} 那么就会保证稍后会自动释放 
    Lock m1(&m);                   // 取得互斥器
    delete bgImage;             //拜托旧的背景图像
    ++imageChanges;             //修改图像变更次数
    bgImage =new Image(imgSrc);//安装新的背景图像
}
