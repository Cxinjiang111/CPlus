/*通过组合模型实现has或者根据某物实现出

*/
#include<string>
#include<list>
class Address{};
class PhoneNumber{};
class Person{
    public:
    private:
        std::string name;
        Address address;
        PhoneNumber voiceNumber;
        PhoneNumber faxNumber;
};
// template<typename T>
// class Set:public std::list<T>
// {

// };

template<typename T>
class Set
{
    public:
    //通过接口函数去操纵成员rep
    bool member(const T&item)const;
    void insert(const T&item);
    void remove(const T&item);
    std::size_t size()const;
    private:
        std::list<T> rep;
};
template<typename T>
bool Set<T>::member(const T&item)const
{

}
template<typename T>
void Set<T>::insert(const T&item)
{

}
template<typename T>
void Set<T>::remove(const T&item)
{

}
template<typename T>
std::size_t Set<T>::size()const
{

}






