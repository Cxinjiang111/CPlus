/************************内存池******************/ 
/* We allocate memory in large chunks in order to avoid fragmenting     */
/* the malloc heap too much.                                            */
/* We assume that size is properly aligned.                             */
/* We hold the allocation lock.                                         */
template <bool __threads, int __inst>
char*
__default_alloc_template<__threads, __inst>::_S_chunk_alloc(size_t __size, 
                                                            int& __nobjs)
{
    char* __result;
    size_t __total_bytes = __size * __nobjs;// 申请的线程池总的空间量
    size_t __bytes_left = _S_end_free - _S_start_free;//内存池剩余空间

    if (__bytes_left >= __total_bytes) {
        // 内存池剩余空间满足需求量 
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return(__result);
    } else if (__bytes_left >= __size) {(__total_bytes,__size]
        // 内存池剩余空间不能满足需求量， 但足够供应一个（含）以上的区块
        __nobjs = (int)(__bytes_left/__size);
        __total_bytes = __size * __nobjs;
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return(__result);
    } else {
        //内存池剩余空间连一个区块的大小都无法提供
        //下次需要申请的总空间，为当前的2倍加上一个对齐
        size_t __bytes_to_get = 
	  2 * __total_bytes + _S_round_up(_S_heap_size >> 4);
        // Try to make use of the left-over piece.
         //以下试着让内存池中的残余零头还有利用价值
        if (__bytes_left > 0) {
            //内存池还有一个零头，先配给适当的free list  
            //首先寻找适当的free list
            _Obj* __STL_VOLATILE* __my_free_list =
                        _S_free_list + _S_freelist_index(__bytes_left);
            //调整free list 将内存池中的残余空间编入
            ((_Obj*)_S_start_free) -> _M_free_list_link = *__my_free_list;
            *__my_free_list = (_Obj*)_S_start_free;
        }
         //配置heap  空间用来补充内存池 _S_start_free分配新空间的新指针
        _S_start_free = (char*)malloc(__bytes_to_get);
        if (0 == _S_start_free) {//新空间内存分配失败
            size_t __i;
            _Obj* __STL_VOLATILE* __my_free_list;
	    _Obj* __p;
            // 试着检视我们手上拥有的东西，这不会造成 我们不打算尝试配置
            // 较少的区块，因为那在多进程机器上容易灾难，以下搜寻适当的free list
            //所谓适当是指 尚有未用区块，且区块够大之 free list
            // Try to make do with what we have.  That can't
            // hurt.  We do not try smaller requests, since that tends
            // to result in disaster on multi-process machines.
            for (__i = __size;
                 __i <= (size_t) _MAX_BYTES;
                 __i += (size_t) _ALIGN) {
                __my_free_list = _S_free_list + _S_freelist_index(__i);
                __p = *__my_free_list;
                if (0 != __p) {// free list 内尚有未用区块 
                    //调整free list 已释放未用区块
                    *__my_free_list = __p -> _M_free_list_link;
                    _S_start_free = (char*)__p;
                    _S_end_free = _S_start_free + __i;
                    // 递归调用自己 为了修正nobjs 注意任何参与零头将被编入适当的free list 中备用
                    return(_S_chunk_alloc(__size, __nobjs));
                    // Any leftover piece will eventually make it to the
                    // right free list.
                }
            }
	    _S_end_free = 0;	// In case of exception. 如果出现意外 内存实在没有了
            _S_start_free = (char*)malloc_alloc::allocate(__bytes_to_get);//调用第一级配置器，看看out-of-memory 机制能否尽力
            // This should either throw an
            // exception or remedy the situation.  Thus we assume it
            // succeeded.
        }
        _S_heap_size += __bytes_to_get;
        _S_end_free = _S_start_free + __bytes_to_get;
        return(_S_chunk_alloc(__size, __nobjs));
    }
}
