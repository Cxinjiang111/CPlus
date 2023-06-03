
template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>::clear()
{
    //把真个表的内部结点给清理掉
    // 遍历到每个桶
  for (size_type __i = 0; __i < _M_buckets.size(); ++__i) {
    _Node* __cur = _M_buckets[__i];
    //遍历到桶的每个结点  
    while (__cur != 0) {
      _Node* __next = __cur->_M_next;
      _M_delete_node(__cur);
      __cur = __next;
    }
    _M_buckets[__i] = 0;
  }
  _M_num_elements = 0;
}


  
template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>
  ::_M_copy_from(const hashtable& __ht)
{
  _M_buckets.clear();//清除桶中的数据 并值0 
  //为已方的buckets vector保留空间，使与对方相同
  //如果己方空间大于对方，就不动，如果己方空间小于对方，就会增大
  _M_buckets.reserve(__ht._M_buckets.size());
  //从已方的bucket vector 尾端开始，插入n个元素，其值为null指针
  //注意 此时buckets vector为空，所以所谓尾端就是起头处 
  _M_buckets.insert(_M_buckets.end(), __ht._M_buckets.size(), (_Node*) 0);
  __STL_TRY {
      //遍历每个桶
    for (size_type __i = 0; __i < __ht._M_buckets.size(); ++__i) {
      // 复制vector的每一个元素，
      const _Node* __cur = __ht._M_buckets[__i];
        if (__cur)  //桶中的结点是否为空 为空就不赋值
        {
            _Node* __copy = _M_new_node(__cur->_M_val);
            _M_buckets[__i] = __copy;
                //拷贝桶中的每个结点
                for (_Node* __next = __cur->_M_next; __next; __cur = __next, __next = __cur->_M_next)
                {
                __copy->_M_next = _M_new_node(__next->_M_val);
                __copy = __copy->_M_next;
                }
        }
    }
    _M_num_elements = __ht._M_num_elements;
  }
  __STL_UNWIND(clear());
}