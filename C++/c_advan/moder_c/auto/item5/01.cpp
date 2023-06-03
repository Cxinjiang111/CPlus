//Prefer auto to explicit type declarations
#include<iostream>
#include<deque>
#include<vector>
#include<functional>
#include<typeinfo>
#include<memory>
using namespace std;
template<typename It>
void dwim(It bm,It e){
    while (bm!=e)
    {
        //迭代器指向的元素的值的类型
        typename std::iterator_traits<It>::value_type;
        currValue=*bm;
    }
    
}
//auto变量从初始化表达式中推导出类型，所以我们必须初始化
void t1(){
    int x1;
    //auto x2;//错误编译器也不知道你是啥
    ///auto x3;
}

//专⽤于Widget类型的⽐较函数
auto derefUPLess = [](const std::unique_ptr<string> &p1,const std::unique_ptr<string> &p2){return *p1<*p2;};
auto derefUPLess = [](auto &p1,auto &p2){return *p1<*p2;};
//funtional
bool (*fun)(const std::unique_ptr<string> &p1,const std::unique_ptr<string> &p2){

};

function<bool(const std::unique_ptr<string> &p1,const std::unique_ptr<string> &p2)> ;
// func();
// 
auto dereUPLess = [](const std::unique_ptr<string> &p1,
const std::unique_ptr<string> &p2){return *p1<*p2;};
/*
语法冗⻓不说，还需要重复写很多形参类型，使⽤ std::function 还不如使⽤auto。⽤auto声明的变
量保存⼀个闭包这个变量将会得到和闭包⼀样的类型。
实例化 std::function 并声明⼀个对象这个对象将会有固定的⼤小。当使⽤这个对象保存⼀个闭包时它
可能⼤小不⾜不能存储，这个时候 std::function 的构造函数将会在堆上⾯分配内存来存储，这就造成
了使⽤ std::function ⽐auto会消耗更多的内存。并且通过具体实现我们得知通过std::function调⽤⼀
个闭包⼏乎⽆疑⽐auto声明的对象调⽤要慢。
换句话说，std::function⽅法⽐auto⽅法要更耗空间且更慢，并且⽐起写⼀⼤堆类型使⽤auto要⽅便得
多。在这场存储闭包的⽐赛中，auto⽆疑取得了胜利（也可以使⽤std::bind来⽣成⼀个闭包，但在
Item34我会尽我最⼤努⼒说服你使⽤lambda表达式代替std::bind)


v.size() 的标准返回类型是 std::vector<int>::size_type ,但是很多程序猿都知道
std::vector<int>::size_type 实际上被指定为⽆符号整型，所以很多⼈都认为⽤ unsigned ⽐写那
⼀⻓串的标准返回类型⽅便。这会造成⼀些有趣的结果。
举个例⼦，在Windows 32-bit上 std::vector<int>::size_type 和 unsigned int 都是⼀样的类
型，但是在Windows 64-bit上 std::vector<int>::size_type 是64位， unsigned int 是32位。这
意味着这段代码在Windows 32-bit上正常⼯作，但是当把应⽤程序移植到Windows 64-bit上时就可能会
出现⼀些问题。
*/
std::vector<int> v;
unsigned sz=v.size();
auto sz=v.size();//不用担心这个平台移植的问题