/*
所谓static 对象，其寿命从被构造出来直到程序结束为止， 因此 stack和heap-based对象都被排除。 
这种对象包括global对象、 定义千namespace作用域内的对象、 在classes内、 在函数内、 
以及在file作用域内被声明为static的对象。函数内的static对象称为local static对象（因为它们对函数而言是local)，
其他static对象称为non-local static对象。 程序结束时static 对象会被自动销毁，
也就是它们 的析构函数会在main(）结束时被自动调用。

所谓编译单元 (translation unit)是指产出单一目标文件(single object file)的
那些源码。 基本上它是单 源码 文件加上其所含入的头文件（扣nclude files)。
现在，我们关心的问题涉及至少两个源码文件，每个内含全少一个non-local static对象
（也就是说该对象是global或位于namespace作用域内， 抑或在class内 或file 作用域内被声明为 static)。
真正的问题是： 如果某编译单元内的某个 non-local static对象的初始化动作使用了另一编译单元内的某个non-local static对象，
它所用到的这个对象可能尚未被初始化， 因为C廿对 “定义千不同编译单元 内的non-local static对象” 的初始化次序并无明确定义。

实例可以帮助理解。 假设你有一个FileSystem class, 它让兀联网上的文件看起来好像位于本机(local)。由于这个class使世界看起来像个单一文件系统，
你可能会产出一个特殊对象，位千global或namespace作用域内，象征单一文件系统 ：
*/
#include<iostream>
#include<string>
#include<list>
using namespace std;
class FileSystem1{
public:
    std::size_t numDisks()const;

};
extern FileSystem1 tfs1;

//-------------------
class FileSystem{
public:
    std::size_t numDisks()const;
    /*
／／同前
//这个函数用来替换tfs对象；它在 I IFileSystemclass中可能是个static。 
／／定义并初始化一个local static对象， 
/／返回一个reference指向上述对象。
／／同前
／／同前， 但原本的referenceto tfs ／／现在改为tfs () 
    */

};
FileSystem&tfs(){
    static FileSystem fs;
    return fs;
}