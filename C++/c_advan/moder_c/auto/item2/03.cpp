/*就像你看到的那样auto类型推断和模板类型推导⼀样⼏乎⼀样的⼯作，
它们就像⼀个硬币的两⾯。
讨论完相同点接下来就是不同点，前⾯我们已经说到auto类型推导和模板类型推导有⼀个例外使得它们
的⼯作⽅式不同，接下来我们要讨论的就是那个例外。
int x1=27;
int x2(27);
int x3={27};
int x47{27};
--->
auto x1=27;
auto x2(27);
auto x3={27};//std::initlizer_list<int>
auto x47{27};
这些声明都能通过编译，但是他们不像替换之前那样有相同的意义。前⾯两个语句确实声明了⼀个类型
为int值为27的变量，但是后⾯两个声明了⼀个存储⼀个元素27的 std::initializer_list<int> 类型的变量
auto  x5={1,2,3.0};//auto 不能推导工作
就像注释说的那样，在这种情况下类型推导将会失败，但是对我们来说认识到这⾥确实发⽣了两种类型
推导是很重要的。⼀种是由于auto的使⽤：x5的类型不得不被推导，因为x5使⽤花括号的⽅式进⾏初始
化，x5必须被推导为 std::initializer_list,但是 std::initializer_list是⼀个模板。
std::initializer_list会被实例化，所以这⾥T也会被推导。 另⼀种推导也就是模板类型推导被归⼊第⼆
种推导。在这个例⼦中推导之所以出错是因为在花括号中的值并不是同⼀种类型。
*/
#include<iostream>
using namespace std;
void t1(){
    //auto x1={1,2,3.0};//错误 这种auto不能推导
    auto x2={1,2,3};//ok x的类型是std::initializer_list<int>
}
 template<typename T>
void f(T param){

}
void t2(){
    auto x2={1,2,3};
    //f({1,2,3});{1,2,3}编译器可能不会把它推导出auto x2 没那么聪明，
    f(x2);
}

template<typename T>
void f(std::initializer_list<T> initList);
void t3(){
    f({1,2,3});//这样告诉了编译器，你要认识{}这个东西哟 
}