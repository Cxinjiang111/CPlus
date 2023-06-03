/* 尽可能延后变量定义式的出现时间

*/
/*
只要你定义了一个变量而其类型带有一个构造函数或析构函数，那么当程序的 
控制流(controlflow)到达这个变量定义式时，你便得承受构造成本；当这个变量 
离开其作用域时，你便得承受析构成本。即使这个变量最终并未被使用，仍需耗费 
这些成本，所以你应该尽可能避免这种情形。
*/
#include<string>
std::string encryptPassword(const std::string&password){
    using namespace std;
    string encrypted;
    if (password.length()<MinimumPawordLength)
    {
        throw logic_error("password is too short");
    }
            //如有必要加一段密码到encrypted
    return encrypted;
}
/*
对象encrypted在此函数中并非完全未被使用，但如果有个异常被丢出，它就真的没被使用。
 也就是说如果函数encryptPassword丢出异常， 你仍得付出 encrypted的构造成本和析构成本。
 所以最好延后encrypted的定义式， 直到确实需要它：
*/
#include<string>
std::string encryptPassword(const std::string&password){
    using namespace std;

    if (password.length()<MinimumPawordLength)
    {
        throw logic_error("password is too short");
    }
    string encrypted;//在上面抛出异常 这个对象就不用申请了，那么构造函数或者其他动作也无需必要了
            //如有必要加一段密码到encrypted
    return encrypted;
}