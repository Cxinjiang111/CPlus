#include<iostream>
#include<string>
#include<vector>
#include<tuple>
using namespace std;
namespace CColor{
 enum color{black,white};  
}
enum Color{black,white,red};
 using userInfo=std::tuple<string,string,size_t>;
enum UserInfoFields{name,email,requtation};
template<typename E>
constexpr typename std::underlying_type<E>::type toUType(E enumerator)noexcept{
    return static_cast<typename std::underlying_type<E>::type>(enumerator);
}
/*
如Item 15提到的，那必须是⼀个constexpr模板函数。
事实上，它也的确该是⼀个constexpr函数，因为它应该能⽤于任何enum。
如果我们想让它更⼀般化，我们还要泛化它的返回类型。较之于返回std::size_t，我们更应该泛化枚举的基础类型。
这可以通过std::underlying_type这个type trait获得。（参⻅Item 9关于type trait的内容）。
最终我们还要再加上noexcept修饰（参⻅Item 14），因为我们知道它肯定不会产⽣异常。
根据上述分析最终得到的toUType模板函数在编译期接受任意枚举名并返回它的值：
*/
template<typename E>
constexpr typename std::underlying_type<E>::type toUType(E enumrator)noexcept
{
    return static_cast<typename std::underlying_type<E>::type>(enumrator);
}
int main(){
    //enum color{black,white};
   // auto white=false;//‘auto white’ redeclared as different kind of entity
    //note: previous declaration ‘main()::color white’
    // enum class color{black,white};// black, white, red限制在Color域内
    // auto white=false;// 没问题，同样域内没有这个名字
    // color c=color::white;
    // CColor::color d=CColor::white;
   
    userInfo info;
    auto val=std::get<1>(info);//不利于观看
    auto val=std::get<email>(info);//这个太得劲了
    auto val=std::get<UserInfoFields::email>(info);//明确添加作用域
    auto val=std::get<static_cast<size_t>(UserInfoFields::email)>(info);//让编译器更加明确的转换从枚举转化成int
//std::get是⼀个模板（函数），需要你给出⼀个std::size_t值的模板实参（注意使⽤<>而不是()），
//因此将枚举名变换为std::size_t值会发⽣在编译期。
    auto val=std::get<toUType(UserInfoFields::email)>(info);
    //toUType 这个东西帮我们去在编译时类型识别，并匹配



    return 0;
}