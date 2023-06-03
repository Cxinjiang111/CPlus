//内存管理
  _Node* _M_new_node(const value_type& __obj)
  {
    _Node* __n = _M_get_node();
    __n->_M_next = 0;
    __STL_TRY {
      construct(&__n->_M_val, __obj);
      return __n;
    }
    __STL_UNWIND(_M_put_node(__n));
  }
  
  void _M_delete_node(_Node* __n)
  {
    destroy(&__n->_M_val);
    _M_put_node(__n);
  }
//构造函数
hashtable(size_type __n,
        const _HashFcn&    __hf,
        const _EqualKey&   __eql,
        const _ExtractKey& __ext,
        const allocator_type& __a = allocator_type())
: __HASH_ALLOC_INIT(__a)
_M_hash(__hf),
_M_equals(__eql),
_M_get_key(__ext),
_M_buckets(__a),
_M_num_elements(0)
{
_M_initialize_buckets(__n);
}

void _M_initialize_buckets(size_type __n)
{
    const size_type __n_buckets = _M_next_size(__n);
    _M_buckets.reserve(__n_buckets);//????
    _M_buckets.insert(_M_buckets.end(), __n_buckets, (_Node*) 0);
    _M_num_elements = 0;
}
//------------------
template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>
  ::resize(size_type __num_elements_hint)
{
//
  const size_type __old_n = _M_buckets.size();
  if (__num_elements_hint > __old_n) {// 这个只是试探
//如果元素个数和bucket vector的大小来比，每个bucket的最大容量和bucket vector的大小相同
// 并不是接近一个百分比，开始扩容的
    const size_type __n = _M_next_size(__num_elements_hint);
    if (__n > __old_n) {
        //设立新的buckets 分配空间
      vector<_Node*, _All> __tmp(__n, (_Node*)(0),
                                 _M_buckets.get_allocator());
      __STL_TRY { //异常保护
          //遍历整个桶的结点
        for (size_type __bucket = 0; __bucket < __old_n; ++__bucket) {
          _Node* __first = _M_buckets[__bucket];
          while (__first) { //遍历每个结点的链子，所有的数据 进行迁移
            size_type __new_bucket = _M_bkt_num(__first->_M_val, __n);
            //令旧bucket指向其所对应之串行的下一个结点
            _M_buckets[__bucket] = __first->_M_next;
            //将当前结点插入到新的bucket内，成为其对应的第一个结点
            __first->_M_next = __tmp[__new_bucket];
            __tmp[__new_bucket] = __first;
            //回到旧bucket所指的待处理串行，准备处理下一个结点
            __first = _M_buckets[__bucket];          
          }
        }
        // 注意，对调两方如果大小不同，大的会变小，小的会变大
        //离开时释放local tmp的内存
        _M_buckets.swap(__tmp);
      }
#         ifdef __STL_USE_EXCEPTIONS
      catch(...) {
        for (size_type __bucket = 0; __bucket < __tmp.size(); ++__bucket) {
          while (__tmp[__bucket]) {
            _Node* __next = __tmp[__bucket]->_M_next;
            _M_delete_node(__tmp[__bucket]);
            __tmp[__bucket] = __next;
          }
        }
        throw;
      }
#         endif /* __STL_USE_EXCEPTIONS */
    }
  }
}

//在不需要重建表格的情况下，插入新结点，键值不允许重复，
//如果能重复插入俺就时multi_xxx 相关容器了
template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
pair<typename hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>::iterator, bool> 
hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>
  ::insert_unique_noresize(const value_type& __obj)
{
  const size_type __n = _M_bkt_num(__obj); //决定obj应为于
  _Node* __first = _M_buckets[__n]; //令first指向bucket对应之串行头部
/*
如果bucket[n]已被占用，此时first将不为0，于是进入以下循环
走过bucket所对应的整个链表 这个unique型的插入 如果时equal 型的插入旧不存在这个问题
*/
  for (_Node* __cur = __first; __cur; __cur = __cur->_M_next) 
 
    if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj)))
    //如果发现与链表中的某键值相同，就不插入，立刻返回
      return pair<iterator, bool>(iterator(__cur, this), false);
//此时没有该值 ，可进行插入
  _Node* __tmp = _M_new_node(__obj);//产生新结点
  __tmp->_M_next = __first;
  _M_buckets[__n] = __tmp;//令新结点成为链表的第一个结点 而且只能有一个
  ++_M_num_elements;      //结点个数累加1
  return pair<iterator, bool>(iterator(__tmp, this), true);
}


//可容纳重复值插入，
template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
typename hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>::iterator 
hashtable<_Val,_Key,_HF,_Ex,_Eq,_All>
  ::insert_equal_noresize(const value_type& __obj)
{
  const size_type __n = _M_bkt_num(__obj);
  _Node* __first = _M_buckets[__n];
    //遍历每个桶
  for (_Node* __cur = __first; __cur; __cur = __cur->_M_next) 
    //遍历每个桶的每个结点，相同就创造结点并作为next的结点 然后就返回
    if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj))) {

      _Node* __tmp = _M_new_node(__obj);
      __tmp->_M_next = __cur->_M_next;
      __cur->_M_next = __tmp;
      ++_M_num_elements;
      return iterator(__tmp, this); 
    }
    //发现没有相同的 那就创建新结点并作为第一个结点
  _Node* __tmp = _M_new_node(__obj);
  __tmp->_M_next = __first;
  _M_buckets[__n] = __tmp;
  ++_M_num_elements;//结点个数累加1
  return iterator(__tmp, this);
}