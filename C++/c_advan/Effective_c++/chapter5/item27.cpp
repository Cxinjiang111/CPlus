/*尽量少做转型动作
C++提供四种新式转型
static_cast<T>：
用来强迫隐式转换，例如将non-const对像转为const对象，或将int转double
const_cast<T>:
通常被用来将对象的常量型转除，它也是唯一有此能力的C++style转型操作符
dynamic_cast<T>
安全向下转型，也就是用来决定某对象是否归属继承体系中的某个类型，
他是唯一无法由旧时语法执行的动作，也是唯一可能耗费重大运行成本的转型动作
reinterpret_cast<T>
意图执行低级转型，实际动作及结果可能取决于编译器，这也就表示它不可移植，
例如将一个Pinter to int 转型为一个int 这一类转型在低级代码以外很少见，
那就是讨论如何针对原始内存写出一个调试用的分配器

·	如果可以， 尽量避免转型， 特别是在注重效率的代码中避免 dynamic_casts。 如果有个设计需要转型动作， 试着发展无需转型的替代设计。
·	如果转型是必要的， 试着将它隐藏千某个函数背后。客户随后可以调用该函数， 而不需将转型放进他们自己的代码内。
·	宁可使用C++-style（新式）转型， 不要使用旧式转型。 前者很容易辨识出来， 而且也比较有着分门别类的职掌。
*/
#include<stdio.h>
#include<iostream>
#include <bitset>///c++中控制进制的头文件
class Widget{
public:
    explicit Widget(int size);
};
// void doSomeWork(const Widget&w);
// doSomeWork(Widget(15));//创建WIdget对象
// doSomeWork(static_cast<Widget>(5));//转型动作创建一个Widget
/*
许多程序员相信，转型其实什么也没做，只是告诉编译器把某种类型视为另一种类型，
这是错误的观念，任何一种转型，往往真的令编译器编译出运行期间执行的代码
*/
int main()
{
    int x=8;
    double y=static_cast<double>(x);    
    std::cout<<std::bitset<64>(x)<<std::endl;
    std::cout<<std::bitset<64>(y)<<std::endl;
    /*代码居然没有改变
0000000000000000000000000000000000000000000000000000000000001000
0000000000000000000000000000000000000000000000000000000000001000
    */
    return 0;
}




