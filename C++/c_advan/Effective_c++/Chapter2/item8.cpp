/*
    别让异常逃离析构函数

析构函数绝对不要吐出 异常。 如果 一个被析构函数调用的函数可能抛出异常，
析构函数应该捕捉任何异常， 然后吞下它们（不传播）或结束程序。

如果客户需要对某个操作函数运行期间抛出的异常做出反应， 那么class应该提供一
个普通函数（而非在析构函数中）执行该 操作。
*/
#include<vector>
using namespace std;

class Widget{
public:
    ~Widget(){} //假设这里可能吐个异常
};

void doSomething(){
    std::vector<Widget> v;

}//v自动被销毁
/*
当vector v被销毁， 它有责任销毁其内含的所有阻dgets。 假设v内含十个
阻dgets, 而在析构第 个元素期间， 有个异常被抛出。 
其他九个Widgets还是应该被销毁（否则它们保存的任何资源都会发生泄漏）， 
因此v应该调用它们各个析构 函数。但假设在那些调用期间， 第二个Widget析构函数又抛出异常。
现在有两个同时作用的异常，这对C丑而言太多了。在两个异常同时存在的情况下， 
程序若不是 结束执行就是导致不明确行为。 本例中它会导致不明确的行为。 
使用标准程序库的 任何其他容器（如list, set)或TRl的任何容器（见条款54)或甚至array,也会出现相同情况。
容器或array并非遇上麻烦的必要条件， 只要析构函数吐出异常，即 使并非使用容器或arrays, 
程序也可能过早结束或出现不明确行为。 是的， C++不 喜欢析构函数吐出异常！
*/

//客户可能会忘记调用调用close 结束服务 
class DBConnection{
public:
    static DBConnection create();

    void close();

};
class DBConn{ //这个类用来管理DBConnection
public:
    ~DBConn() //确保数据库连接总是会被关闭
    {
        db.close();
    }
    void close();
private:
    DBConnection db;    
};
//不让异常继续传播 从而减少查找错误的位置的代价
DBConn::~DBConn()
{
    try
    {
        db.close();
    }
    catch(...){
        std::abort();
    }
}
//




