#include<iostream>
#include<string>
#if 0
namespace std{
    template<typename T>            //返回值和参数传入均为右值，
    typename remove_reference<T>::type&&move(T&&param){
        using ReturnType=typename remove_reference<T>::type&&;//利用using申明
        return static_cast<ReturnType>(param);
    }
    //这个函数好像就做一个类型转换
    //std::move接受⼀个对象的引⽤（准确的说，⼀个通⽤引⽤(universal reference)，后⻅Item 24)，返回⼀个指向同对象的引⽤。
    /*
该函数返回类型的&&部分表明std::move函数返回的是⼀个右值引⽤，但是，正如Item 28所解释的那
样，如果类型T恰好是⼀个左值引⽤，那么T&&将会成为⼀个左值引⽤。为了避免如此，类型萃取器
（type trait，⻅Item 9) std::remove_reference应⽤到了类型T上，因此确保了&&被正确的应⽤到
了⼀个不是引⽤的类型上。这保证了std::move返回的真的是右值引⽤，这很重要，因为函数返回的右
值引⽤是右值（rvalues)。因此，std::move将它的参数转换为⼀个右值，这就是它的全部作⽤。
    */
   /*
   因为std::move除了转换它的参数到右值以外什么也不做，有⼀些提议说它的名字叫rvalue_cast可
能会更好。虽然可能确实是这样，但是它的名字已经是std::move，所以记住std::move做什么和不
做什么很重要。它其实并不移动任何东西。
  当然，右值本来就是移动操作的侯选者，所以对⼀个对象使⽤std::move就是告诉编译器，这个对象很
适合被移动。所以这就是为什么std::move叫现在的名字: 更容易指定可以被移动的对象。 
   */
}
#endif

// class Annotation{
// public:
//     explicit Annotation(std::string text);
//     //explicit Annotation(const std::string text);
//     //但是Annotation类的构造函数仅仅是需要读取参数text的值，它并不需要修改它。为了和历史悠久的
// //传统：能使⽤const就使⽤const保持⼀致，你修订了你的声明以使text变成const，
// //当复制参数text到⼀个数据成员的时候，为了避免⼀次复制操作的代价，你仍然记得来⾃Item 41的建
// //议，把std::move应⽤到参数text上，因此产⽣⼀个右值，
// };
class Annotation{
public:
//既然上面在构造函数确实不需要额外拷贝，直接使用move如下
    explicit Annotation(const std::string text):value(std::move(text)){}

private:
    std::string value;
};
/*
这段代码可以编译，可以链接，可以运⾏。这段代码将数据成员value设置为text的值。这段代码与
你期望中的完美实现的唯⼀区别，是text并不是被移动到value，而是被复制。诚然，text通过
std::move被转换到右值，但是text被声明为const std::string，所以在转换之前，text是⼀个
左值的const std::string，而转换的结果是⼀个右值的const std::string，但是纵观全程，
const属性⼀直保留。
*/
int main(){
    Annotation a("hello");

    return 0;


}