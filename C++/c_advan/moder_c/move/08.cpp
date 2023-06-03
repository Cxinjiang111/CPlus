#include<string>
template<typename T>
class Array{
    public:
    //这个成员变多时 swap需要重新改写，感觉之前合起来写没多大区别
        void swap(Array &other)noexcept{
            using std::swap;
            swap(m_size,other.m_size);
            swap(m_data,other.m_data);
        }
    //Array other 这里传的是值。那么当传入的是左值，other会拷贝一份进行赋值，
    //当other传入是右值时，这时就不会move语义拷贝资源，然后交换 
    Array &operator=(Array other)noexcept{
        swap(other);
        return *this;
    }
    //wo obtain both a copy-assignment operator and a move-assignment operator   
};
class Widget{
    Array<int> m_array;
    std::string m_str;
    public:
        Widget(Widget&&other)noexcept:
            m_array(std::move(other.m_array)),m_str(std::move(other.m_str)){}
        Widget&operator=(Widget&&other)noexcept{
            m_array=std::move(other.m_array);
            m_str=std::move(other.m_str);
            return *this;
        }

};