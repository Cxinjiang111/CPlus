#include<iostream>
using namespace std;
const int i=0;//decltype(i)是const int 
bool f(const widget&w);//-->const widget&
struct point{
    int x; //-->point::x    int;
    int y; //-->point::x  int; 
};
template <typename T>
class Vector{
    T&operator[](std::size_t iondex);
};
Vector<int> v;
/*
在C++11中，decltype最主要的⽤途就是⽤于函数模板返回类型，而这个返回类型依赖形参。举个例
⼦，假定我们写⼀个函数，⼀个参数为容器，⼀个参数为索引值，这个函数⽀持使⽤⽅括号的⽅式访问
容器中指定索引值的数据，然后在返回索引操作的结果前执⾏认证⽤⼾操作。函数的返回类型应该和索
引操作返回的类型相同。

*/

