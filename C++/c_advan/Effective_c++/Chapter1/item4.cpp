/* 确定对象被使用前已先被初始化
永远在使用对象之前将它初始化，对于无任何成员的内置类型，你必须手工完成此事

*/
//别混淆了赋值和初始化
#include<iostream>
#include<string>
#include<list>
using namespace std;
class PhoneNumber{};
class ABEntry{
public:
    ABEntry(const std::string &name,const std::string &address,
            const std::list<PhoneNumber>&phones);
            //C++规定对象成员变量的初始化动作发生在进入结构函数本体之前，初始化发生地更早 发生在这些成员地默认构造函数被自动调用之时
    ABEntry(const std::string &name,const std::string &address,
            const std::list<PhoneNumber>&phones):theName(name),theAddress(address),
            thePhones(phones),numTimesConsulted(0){};//初始化
private:
    std::string theName;
    std::string theAddress;
    std::list<PhoneNumber> thePhones;
    int numTimesConsulted;
};
//赋值而非初始化
ABEntry::ABEntry(const std::string &name,const std::string &address,const std::list<PhoneNumber>&phones)
{
    theName=name;
    theAddress=address;
    thePhones=phones;
    numTimesConsulted=0;
}
/*
C++有着十分固定 地成员初始化次序，base classes更早于其derived class被初始化，
class地成员变量总是以其声明次序初始化 比如 theName要不theAddress要先被初始化 即使程序员自己随意书写地次序 也不会有任何影响
*/

