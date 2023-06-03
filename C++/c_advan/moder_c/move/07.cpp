#include<string>

//产生一个右值
std::string s;
std::string s2(static_cast<std::string&&>(s));
//static_cast<std::string&&>产生一个右值move 也是这种方式构造move函数
template<typename T>
[[nodisacrd]] constexpr auto move(T&&)noexcept->std::remove_reference_t<T>&&{
    return static_cast<std::remove_reference_t<T>&&>(t);
}
