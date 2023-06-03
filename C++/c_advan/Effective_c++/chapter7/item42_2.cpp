/*
"typename必须作为嵌套从属类型名称的前缀词 “ 这一规则的例外是， 
typename不可以出现在base classes list内的嵌套从属类型名称之前，
也不可在member initialization list（成员初值列）中作为base class修饰符。 例如：
*/
class Neste
{
    public:
    Neste(int x1):x(x1){};
private:
int x;
};
template<typename T>
class Base{
public:
    typedef T* const_iterator; 
    typedef Neste Nested ;
};

template<typename T>
class Derived:public Base<T>::Nested //base class list中不允许typename
{
    public:
        explicit Derived(int x):Base<T>::Nested(x)
        { // mem init list不允许typename 嵌套从属类型名称
            typename Base<T>::Nested temp;//
            //既不在base class list中也不在mem. init. list中， 
            //作为一个base class修饰符需加上typename.
        }

};



