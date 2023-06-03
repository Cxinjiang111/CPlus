/*
但是，允许impure virtual函数同时指定函数声明和函数缺省行为，却有可能造成危险。 
欲探讨原因，让我们考虑XYZ航空公司设计的飞机继承体系。该公司只 
有A型和B型两种飞机，两者都以相同方式飞行。因此XYZ设计出这样的继承体 系：

*/
class Airport{

};
class Airplane{
public:
    virtual void fly(const Airport &destination);

};
void Airplane::fly(const Airport &destination)
{

}
void Airplane::fly(const Airport &destination)
{

}
class ModelA:public Airplane{};
class ModelB:public Airplane{};
/*
为了表示所有飞机都一定能飞， 并阐明 “不同型飞机原则上需要不同的fly实现“, 
Airplane:: fly被声明为virtual。 然而为了避免在ModelA和ModelB中撰写
相同代码，缺省飞行行为由沁rplane:: fly提供，它同时被ModelA和ModelB继承。

这是个典型的面向对象设计。两个classes共享－份相同性质（也就是它们实现 fly的方式）， 
所以共同性质被搬到base class中， 然后被这两个classes继承。 这 个设计突显出共同性质，
 避免代码重复， 并提升未来的强化能力， 减缓长期维护所需的成本。
 所有这些都是面向对象技术如此受到欢迎的原因。XYZ航空公司应该感到骄傲。
现在， 假设XYZ盈余大增， 决定购买一种新式C型飞机。C型和A型以及B 型有某些不同。 更明确地说， 它的飞行方式不同。
*/
class ModelC:public Airplane{
            // 未写fly函数
};
/*
XYZ公司的程序员在继承休系中针对C型飞机添加了一个class, 但由于他们急看让新飞机上线服务， 竞忘了重新定义其fly函数：
问题不在Airplane:: fly有缺省行为，而在千ModelC在未明自说出 “ 我要“ 的情况下就继承了该缺省行为。
 幸运的是我们可以轻易做到 “提供缺省实现给 derived classes, 但除非它们明白要求否则免谈” 。 
 此间技俩在千切断 “virtual函数接口” 和其 “ 缺省实现“ 之间的连接。 下面是一种做法：
*/
