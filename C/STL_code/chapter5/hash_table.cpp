/*线性探测 Clinear probing) 
首先让我们认识一个名词：负载系数(loading factor)，意指元素个数除以表格大小。
 负载系数永远在0~1之间一除非采用开链(separate chaining)策略， 后述。
当hashfunction计算出某个元素的插入位置，而该位置上的空间已不再可用时，我们应该怎么办？
最简单的办法就是循序往下一一寻找（如果到达尾端，就绕 到头部继续寻找），
直到找到一个可用空间为止。只要表格（亦即array)足够大， 总是能够找到一个安身立命的空间，
但是要花多少时间就很难说了。进行元素搜寻 操作时，道理也相同，
如果hashfunction计算出来的位置上的元素值与我们的搜寻 目标不符，
就循序往下一一寻找，直到找到吻合者，或直到遇上空格元素。
至千元 素的删除，必须采用惰性删除(lazydeletion) ,也就是只标记删除记号，
实际删 除操作则待表格重新整理(rehashing)时再进行一一这是因为hashtable中的每一
个元素不仅表述它自己，也关系到其它元素的排列。
*/
 /*
 hashtable迭代器必须永远维系着整个”bucketvector“的关系 并记录目前所指的结点 
 其前进操作是首先尝试从目前所指的结点出发，前进一个位置，由于结点被安置于list内，
 所以利用结点的next 指针即可轻松达成前景操作，如果目前结点正巧是list的尾端
 就跳到下一个bucket身上，那么正是指向下一个list的头部结点
 */
template <class _Val, class _Key, class _HashFcn,
          class _ExtractKey, class _EqualKey, class _Alloc>
struct _Hashtable_iterator {
  typedef hashtable<_Val,_Key,_HashFcn,_ExtractKey,_EqualKey,_Alloc>
          _Hashtable;
  typedef _Hashtable_iterator<_Val, _Key, _HashFcn, 
                              _ExtractKey, _EqualKey, _Alloc>
          iterator;
  typedef _Hashtable_const_iterator<_Val, _Key, _HashFcn, 
                                    _ExtractKey, _EqualKey, _Alloc>
          const_iterator;
  typedef _Hashtable_node<_Val> _Node;

  typedef forward_iterator_tag iterator_category;
  typedef _Val value_type;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef _Val& reference;
  typedef _Val* pointer;

  _Node* _M_cur; //迭代器目前所指的结点
  _Hashtable* _M_ht; //保持对容器的连结关系 因为可能需要从bucket跳到bucket

  _Hashtable_iterator(_Node* __n, _Hashtable* __tab) 
    : _M_cur(__n), _M_ht(__tab) {}
  _Hashtable_iterator() {}
  reference operator*() const { return _M_cur->_M_val; }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */
  iterator& operator++();
  iterator operator++(int);
  bool operator==(const iterator& __it) const
    { return _M_cur == __it._M_cur; }
  bool operator!=(const iterator& __it) const
    { return _M_cur != __it._M_cur; }
};
//-------------

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, 
          class _All>
_Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>&
_Hashtable_iterator<_Val,_Key,_HF,_ExK,_EqK,_All>::operator++()
{
  const _Node* __old = _M_cur;
  _M_cur = _M_cur->_M_next;如果存在，就是它，否则进入以下if流程
  if (!_M_cur) {
    size_type __bucket = _M_ht->_M_bkt_num(__old->_M_val);
    while (!_M_cur && ++__bucket < _M_ht->_M_buckets.size())
      _M_cur = _M_ht->_M_buckets[__bucket];
  }
  return *this;
}