//C++ new handler 机制是 一旦::operator new 无法完成任务时 在丢出std::
//bad_alloc 异常状态之前，会先调用由客服端指定的处理例程 
//
  enum {_ALIGN = 8};  //小型区块的上调边界
  enum {_MAX_BYTES = 128};//小型区块的上调边限
  enum {_NFREELISTS = 16}; // _MAX_BYTES/_ALIGN free-lists 个数
template <bool threads, int inst>
void*
__default_alloc_template<threads, inst>::reallocate(void* __p,
                                                    size_t __old_sz,
                                                    size_t __new_sz)
{
static size_t
  _S_round_up(size_t __bytes) // 将bytes上调至8的倍数 记住  
    { return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }

__PRIVATE: 
//这里？？？？
  union _Obj { // free-lists 的节点构造
        union _Obj* _M_free_list_link; //指针 指向相同形式的另一个Obj 
        char _M_client_data[1];    /* The client sees this.        */
  };
private:
# if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
    static _Obj* __STL_VOLATILE _S_free_list[]; 
        // Specifying a size results in duplicate def for 4.1
# else
    static _Obj* __STL_VOLATILE _S_free_list[_NFREELISTS]; 
# endif
  static  size_t _S_freelist_index(size_t __bytes) {
      //根据区块的大小 决定释放的区块索引号
        return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
        //返回一个大小为n的对象，并可能加入大小为n的其他区块到free list
  }

  // Returns an object of size __n, and optionally adds to size __n free list.
  static void* _S_refill(size_t __n);
  // Allocates a chunk for nobjs of size size.  nobjs may be reduced
  // if it is inconvenient to allocate the requested number.
  // 配置一大块空间，可容纳nobjs个大小为size的区块  预分配一定量的空间
  //如果配置nobjs个区块有所不便，nobjs可能会降低
  static char* _S_chunk_alloc(size_t __size, int& __nobjs);

  // Chunk allocation state.
  static char* _S_start_free;//内存池起始位置 只在chunk_alloc()中变化
  static char* _S_end_free;//内存池结束位置 只在chunk_alloc()中变化
  static size_t _S_heap_size;




//           空间配置函数       
public:

  /* __n must be > 0      */
  static void* allocate(size_t __n)
  {
    void* __ret = 0;
    //大于128 就调用第一级配置器
    if (__n > (size_t) _MAX_BYTES) {
      __ret = malloc_alloc::allocate(__n);
    }
    else { //需分配的内存较少 调用第二级分配器
        //寻找16个free list中适当的一个
      _Obj* __STL_VOLATILE* __my_free_list
          = _S_free_list + _S_freelist_index(__n);
      // Acquire the lock here with a constructor call.
      // This ensures that it is released in exit or during stack
      // unwinding.
#     ifndef _NOTHREADS
      /*REFERENCED*/
      _Lock __lock_instance;
#     endif
      _Obj* __RESTRICT __result = *__my_free_list;
      if (__result == 0)
      //没找到适合大小的free list 准备重新填充free list在原有的空间上乘以2
        __ret = _S_refill(_S_round_up(__n));
      else {
          //调整free list
        *__my_free_list = __result -> _M_free_list_link;
        __ret = __result;
      }
    }

    return __ret;
  };
/*                    空间释放函数                      */ 
//----这个有点没太懂，小区域怎么根据释放的大小 找到释放的位置？？？
  /* __p may not be 0 */
  static void deallocate(void* __p, size_t __n)
  {   
    if (__n > (size_t) _MAX_BYTES)
      malloc_alloc::deallocate(__p, __n);
    //  第释放的空间大于128说明在小区域块内申请的，在小区域内寻找兵释放该区域即可
    else {//寻找需要释放区块的位置 _S_freelist_index(__n);在第几个next上
      _Obj* __STL_VOLATILE*  __my_free_list  //指针类型
          = _S_free_list + _S_freelist_index(__n);
      _Obj* __q = (_Obj*)__p;

      // acquire lock
#       ifndef _NOTHREADS
      /*REFERENCED*/
      _Lock __lock_instance;
#       endif /* _NOTHREADS */ // 调整free list 回收区块
      __q -> _M_free_list_link = *__my_free_list;
      *__my_free_list = __q;
      // lock is released here
    }
  }

  static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz);

} ;
template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_start_free = 0;

template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_end_free = 0;

template <bool __threads, int __inst>
size_t __default_alloc_template<__threads, __inst>::_S_heap_size = 0;

template <bool __threads, int __inst>
typename __default_alloc_template<__threads, __inst>::_Obj* __STL_VOLATILE
__default_alloc_template<__threads, __inst> ::_S_free_list[
# if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
    _NFREELISTS
# else
    __default_alloc_template<__threads, __inst>::_NFREELISTS
# endif
] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };