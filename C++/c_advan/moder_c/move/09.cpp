#include<vector>
template<typename T,typename Alloc>
void vector<T,Alloc>::realloc(size_t cap){
    using all_tr=std::allocatot_traits<Alloc>;
    auto new_data=all_tr::alocate(s_alloc,cap),p=new_data;
    try{
        for(size_type i=0;i!=m_size;++i,++p){
            all_tr::construct(s_alloc,p,m_data[i]);
        }
    }
    catch(...){
        //那异常之前申请的所有内存一一释放掉
        while (p!=new_data)
        {
            all_tr::destory(s_alloc,--p);
            all_tr::deallocate(s_alloc,new_data,cap);
            throw;
            /* code */
        }
        
    }
    m_free();
    m_data=new_data;
    m_capacity=cap;
}
//异常不欢迎移动