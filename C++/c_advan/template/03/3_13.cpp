class MyIterator {
public:
    MyIterator(int id)
    {
        m_iter = IteratorCreate();
        m_obj = IteratorGet(m_iter);
        std::cout << m_obj << " enhanced " << this << std::endl;
    }

    MyIterator()
    {
        std::cout << m_obj << " default " << this << std::endl;
    }

    bool operator!=(const MyIterator& other)
    {
        return (m_obj != other.m_obj);
    }

    const MyIterator& operator++()
    {
        IteratorNext(m_iter);
        m_obj = IteratorGet(m_iter);
        return *this;
    }

    CNeoPersist* operator*()
    {
        if (m_iter)
            return m_obj;
        else
            return nullptr;
    }

    ~MyIterator()
    {
        std::cout << m_iter << " " << this << std::endl;
    }

private:
    CIterator* m_iter = nullptr;
    CNeoPersist* m_obj = nullptr;
};

class MyContainer
{
public:

    MyIterator begin() const { return begin_; }
    MyIterator end() const { return end_; }
    MyContainer(int id) : begin_(id), end_() {}

private:
MyIterator begin_;
MyIterator end_;
};