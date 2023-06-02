#include<string>
template<typename T>
class NameObject{
public:
    NameObject(std::string&name,const T&value);
    //
private:
    std::string& nameValue;
    const T objectValue;
};
int main()
{
    std::string newDog("persephone");
    std::string oldDog("satch");
    NameObject<int> p(newDog,2);
    //NameObject<int> s(oldDog,36);
    //p=s;//编译不过去 error
    /*
赋值之前， 不论p.nameValue和 s.nameValue都指向string对象（当然不是同一个）。
赋值动作该如何影响p.nameValue呢？ 赋值之后p.nameValue应该 
指向s.nameValue所指的那个string吗？也就是说reference自身可被改动吗？如果是，
那可就开辟了新天地， 因为C+＋并不允许 “ 让reference改指向不同对象 ” 。
    
换一个想法，p.nameValue所指的那个string对象该被修改，进而影响或references而且指向该string"的其他对象吗？
也就是对象不被直接牵扯到作内？编译器生成的copy assignment操作符究竟该怎么做呢？

面对这个难题，C++的响应是拒绝编译那一行赋值动作。如果你打算在一个“ 内 
含reference成员” 的class内支持赋值操作(assignment)， 你必须自己定义copy assignment操作符。 
面对 “内含const成员 ” （如本例之objectValue)的classes,编译器的反应也一样。 更改const成员是不合法的，
所以编译器不知道如何在它自己生成的赋值函数内面对它们。 最后还有一种情况： 
如果某个base classes将copy assignment操作符声明为private， 编译器将拒绝为其derivedclasses生成一个copy assignment操作符。
毕竟编译器为derived classes所生的copy assignment操作符想 象中可以处理baseclass成分（见条款12)，
但它们当然无法调用derivedclass无权 调用的成员函数。 编译器两手一摊， 无能为力。
    */
}