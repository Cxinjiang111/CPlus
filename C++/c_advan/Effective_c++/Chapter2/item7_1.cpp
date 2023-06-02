
/*
如果class不含virtual函数，通常表示它并不意图被用做一个base class ，当class
不企图被用作base class 相反令其析构函数为virtual往往是个馊主意

如果1砒占用32 bits，那么Point对象可塞入一个64-bit缓存器中。 
更有甚者， 这样一个Point对象可被当做一个 “64-bit量 ” 传给以其他语言如C或FORTRAN撰写的函数。
 然而当Poi正的析构函数是virtual, 形势起了变化。

欲实现出virtual函数， 对象必须携带某些信息， 主要用来在运行期决定哪一个 virtual函数该被调用。 
这份信息通常是由一个所谓vptr (virtual table pointer)指针指 出。vptr 指向 一个由函数指针构成的数组，
称为vtbl (virtual table)；每一个带有virtual 函数的class都有一个相应的vtbr。 
当对象调用某一 virtual闭数， 实际被调用的函数取决于该对象的vptr所指的那个vtb|——编译器在其中寻找适当的函数指针。

virtual函数的实现细节不重要。重要的是如果Pointclass内含virtual函数，其对象的体积会增加：
在32-bit计算机体系结构中将占用64bits（为了存放两个ints) 至96 bits（两个ints加上vptr):  64-bit计算机体系结构中可能占用64-128bits, 
囚为指针在这样的计算机结构中占64bits。因此，为Point添加一个vptr会增加其 对象人小达50%~100%!Point对象个再能够塞入一个64-bit缓存器，
而C++的Point 对象也不再和其他语言（如C)内的相同声明有着样的结构（囚为其他语言的对 应物并没有vptr)，
因此也就不再可能把它传递至（或接受自）其他语言所写的函 数，除非你明确补偿vptr--那属千实现细节，也因此不再具有移植性。

因此， 无端地将所 有classes的析构函数声明为 virtual,就像从未声明它们为 virtual 一样，都是错误的。
许多人的心得是：只有当class内含全少一个virtual函数， 才为它声明virtual析构函数。
class SpecialString:public std::string{ //string 是个non-virtual析构函数

};
SpecialString*pss=new SpecialString("hekllo");
std::string *ps;
ps=pss
delete ps; //这样会导致内存泄漏
*/
#include<iostream>
using namespace std;
class Point{
public:
    Point(){};
    Point(int xCoord,int yCoord);
    virtual ~Point()=0;//不能为带有纯虚函数的类创建对象，也就时不能被实体化 instantiated的
private:
    int x,y;
};
/*
时候令class带一个purevirtual析构函数，可能颇为便利。还记得吗，purevirtual 函数导致abstract（抽象）
classes一—也就是不能被实体化(instantiated)的class。 也就是说，你不能为那种类型创建对象。
然而有时候你希望拥有抽象class,但手上 没有任何purevirtual函数，怎么办？唔，
由千抽象class总是企图被当作一个baseclass 来用，而又由于baseclass应该有个virtual析构函数，
并且由千purevirtual函数会导 致抽象class，因此解法很简单：为你希望它成为抽象的那个class声明一个purevirtual析构函数。

*/
class AWOV{ //抽象类
public:
    AWOV(){
        cout<<"AWOV"<<endl;
    };
    virtual ~AWOV()=0;//纯虚函数
};
/*
这个class有一个purevirtual函数，所以它是个抽象class,又由于它有个virtual析构函数，所以你不需要担心析构函数的问题。
然而这里有个窍门：你必须为这个 pure virtual析构函数提供一份定义：
*/
AWOV::~AWOV(){}
class BWOV:public AWOV{
public:
    BWOV(){
        cout<<"BWOV"<<endl;
    }
    ~BWOV(){
        cout<<"~BWOV"<<endl;   
    }

};
int main()
{
    //Point a;
    //BWOV a;
    //这样就可以了
    AWOV *p=new BWOV();
    delete p;
    return 0;
}
/*
析构函数的运作方式是，最深层派生(mostderived)的那个class其析构函数最
先被调用，然后是其每一个baseclass的析构函数被调用。编译器会在AWOV的derived
classes的析构函数中创建一个对～AWOV的调用动作， 所以你必须为这个函数提供一 份定义。
 如果不这样做， 连接器会发出抱怨。

给base classes 一个virtual析构函数 ” ，这个规则只适用于polymorphic（带多态性质的）baseclasses身上。
这种base classes的设计目的是为了用来“ 通过baseclass 接口处理derivedclass对象” 。
TimeKeeper就是一个polymorphicbase class, 因为我们希望处理AtomicClock和WaterClock对象，
纵使我们只有TimeKeeper指针指向它们。

并非所有base classes的设计目的都是为了多态用途。 例如标准string和STL容器都不被设计作为baseclasses使用，
更别提多态了。某些classes的设计目的是作 为base classes使用，但不是为了多态用途。
 这样的class es如条款6的Uncopyable 和标准程序库的input_iterator_tag（条款47)，
 它们并非被设计用来 “经由base class接口处置derived class对象” ， 因此它们不需要virtual析构函数。

*/
