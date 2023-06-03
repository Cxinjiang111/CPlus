
//内存池空间不够了
返回一个大小为n的对象，并且有时候会为适当的free list 增加结点
//假设n已经适当上调至8的倍数
/* Returns an object of size __n, and optionally adds to size __n free list.*/
/* We assume that __n is properly aligned.                                */
/* We hold the allocation lock.                                         */
template <bool __threads, int __inst>
void*
__default_alloc_template<__threads, __inst>::_S_refill(size_t __n)
{
    int __nobjs = 20;
    //调用chunk_alloc(),尝试取得nobjs个区块作为free list 的新节点
    //注意参数nobjs是pass by reference 
    char* __chunk = _S_chunk_alloc(__n, __nobjs);//新地址
    _Obj* __STL_VOLATILE* __my_free_list;
    _Obj* __result;
    _Obj* __current_obj;
    _Obj* __next_obj;
    int __i;
    //如果只获得一个区块，这个区块就分配给调用者用，free list无新节点
    if (1 == __nobjs) return(__chunk);
     //否则 准备调整free list 纳入新节点
    __my_free_list = _S_free_list + _S_freelist_index(__n);
    //以下在chunk 空间内建立 free list 
    /* Build free list in chunk */
      __result = (_Obj*)__chunk;// 这一块准备返回给客服端
      //以下导引free list 指向新配置的空间（取自内存池）
      *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
      // 以下将free list 的各节点串接起来
      for (__i = 1; ; __i++) { // 从1 开始  因为第0个将给返回给客端
        __current_obj = __next_obj;//指针不断向前进
        __next_obj = (_Obj*)((char*)__next_obj + __n);
        if (__nobjs - 1 == __i) {
            __current_obj -> _M_free_list_link = 0;
            break;
        } else {
            __current_obj -> _M_free_list_link = __next_obj;
        }
      }
    return(__result);
}
