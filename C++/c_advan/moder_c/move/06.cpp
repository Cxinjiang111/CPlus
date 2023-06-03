//the move constructor
template<typename T>
class Array{
    std::size_t m_size;
    T*m_data;
    public:
        //移动操作的构造函数
        Array(Array&&other)noexcept:
        //m_data(other.m_data)这个m_data并没有开辟新空间，初始化赋值
        m_size(other.m_size),m_data(other.m_data){//this拿到资源值
        //切断other与内存之间的联系，同时也将other置为一种安全可析构的地方
            other.m_data=nullptr;//将other的属性边为空
            other.m_size=0;
        }
/*
obtain the resource directly instead of making of copy

*/




        //移动赋值运算符
        Array&operator=(Array&&other)noexcept{
            if(this!=&other)
            {
                delete[] m_data;
                m_size=other.m_size;
                m_data=other.m_data;
                other.m_data=nullptr;
                other.m_size=0;
            }
            return *this; 
        }
};

