#include<iostream>
//G4.9__pool_alloc  分配池
class __pool_alloc_base{
protected:
    enum{_S_align=8};//
    enum{_S_max_bytes=128};
    enum{_S_free_list_size=(size_t)_S_max_bytes/(size_t)_S_align};
    union{
        union _Obj*_M_free_list_link;
        char _M_client_date[1];
    };
    static _Obj*volatile _S_free_list[_S_free_list_size];
    static char*_S_start_free;
    static char* _S_end_free;
    static size_t _S_heap_size;
    public:
      char*  _M_allocate_chunk(size_t _n,int&_nobjs);
};
char*__pool_alloc_base::_M_allocate_chunk(size_t _n,int&_nobjs)
{
    char *_result;
    size_t _total_bytes=_n*_nobjs;//申请的总的空间数
    size_t _bytes_left=_S_end_free-_S_start_free;
    size_t __bytes_to_get=_total_bytes-_bytes_left;
    __try{
        _S_start_free=static_cast<char*>(::operator new(__bytes_to_get));
    }
    __catch(const std::bad_alloc&){
        size_t _i=_n;
        for(;_i<=(size_t)_S_max_bytes;_i+=(size_t)_S_align)
        {

        }
        //catch成功的话，是不是就返回了？？
        //当我们没有更多的内存 再抛异常
        _S_start_free=_S_end_free=0;//
        __throw_exception_again;
    }
    _S_heap_size+=__bytes_to_get;
    _S_end_free=_S_start_free+__bytes_to_get;
    return _M_allocate_chunk(_n,_nobjs);//???这里怎么又返回了递归了呢？？？
}