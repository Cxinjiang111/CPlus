template<typename T>
class Array{
    std::size_t m_size;
    T*m_data;
    public:
    Array*operator=(Array&&other) noexcept{
        if(this!=other){
            delete[] m_data;
            m_size=other.m_size;
            m_data=other.m_data;
            other.m_size=0;
            other.m_data=nullptr;
            
        }
        return *this;
    }
};
/*
test self-assignment directly
obtain the resource 

*/