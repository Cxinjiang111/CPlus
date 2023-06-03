template<class T>
class allocator{
public:
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef T*          pointer;
    typedef T           value_type;
    pointer allocate(size_type n,allocator<void>::const_pointer=0)
    {
        //最终还是调用operator new 和operator delete
        pointer tmp=
        _RWSTD_STATIC_CAST(pointer,(::operator new 
        (_RWSTD_STATIC_CAST(size_t ,(n*sizeof*(value_type)))));
        _RWSTD_THROW_NO_MSG(tmp==0,bad_alloc);
        return tmp;
        void dellocate(pointer p,size_type)
        {
            ::operator delete(p);//调用全局的delete
        }
    } 
};