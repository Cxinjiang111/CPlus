//元素的插入和查询
template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::operator=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x)
{
  if (this != &__x) {
    // Note that _Key may be a constant type.
    clear();
    _M_node_count = 0;
    _M_key_compare = __x._M_key_compare;        
    if (__x._M_root() == 0) {
      _M_root() = 0;
      _M_leftmost() = _M_header;
      _M_rightmost() = _M_header;
    }
    else {
      _M_root() = _M_copy(__x._M_root(), _M_header);
      _M_leftmost() = _S_minimum(_M_root());
      _M_rightmost() = _S_maximum(_M_root());
      _M_node_count = __x._M_node_count;
    }
  }
  return *this;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::_M_insert(_Base_ptr __x_, _Base_ptr __y_, const _Value& __v)
{
  _Link_type __x = (_Link_type) __x_;
  _Link_type __y = (_Link_type) __y_;
  _Link_type __z;

  if (__y == _M_header || __x != 0 || 
      _M_key_compare(_KeyOfValue()(__v), _S_key(__y))) {
    __z = _M_create_node(__v);
    _S_left(__y) = __z;               // also makes _M_leftmost() = __z 
                                      //    when __y == _M_header
    if (__y == _M_header) {
      _M_root() = __z;
      _M_rightmost() = __z;
    }
    else if (__y == _M_leftmost())
      _M_leftmost() = __z;   // maintain _M_leftmost() pointing to min node
  }
  else {
    __z = _M_create_node(__v);
    _S_right(__y) = __z;
    if (__y == _M_rightmost())
      _M_rightmost() = __z;  // maintain _M_rightmost() pointing to max node
  }
  _S_parent(__z) = __y;
  _S_left(__z) = 0;
  _S_right(__z) = 0;
  _Rb_tree_rebalance(__z, _M_header->_M_parent);
  ++_M_node_count;
  return iterator(__z);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::insert_equal(const _Value& __v)
{
  _Link_type __y = _M_header;
  _Link_type __x = _M_root();
  while (__x != 0) { //查找是否存在重复值
    __y = __x;
    __x = _M_key_compare(_KeyOfValue()(__v), _S_key(__x)) ? 
            _S_left(__x) : _S_right(__x); //比较 遇大 说明自己小，对比的太大了，则往左 寻找小的，遇到小于或等于 则往右
  } //
  return _M_insert(__x, __y, __v);//实现真正的插入操作的函数
}


template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
pair<typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator, 
     bool>
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::insert_unique(const _Value& __v)
{
  _Link_type __y = _M_header;
  _Link_type __x = _M_root(); //从根结点开始
  bool __comp = true;
  while (__x != 0) { //根节点不为空，往下寻找适当的插入点
    __y = __x;
    __comp = _M_key_compare(_KeyOfValue()(__v), _S_key(__x));
    __x = __comp ? _S_left(__x) : _S_right(__x);//比较 遇大 说明自己小，对比的太大了，则往左 寻找小的，遇到小于或等于 则往右
  }//离开while循环之后，y所指即插入点之父节点
  iterator __j = iterator(__y); //令迭代器j指向插入点之父节点y   
  if (__comp) //如果离开while循环时，comp为真，（表示遇大 将插入于左侧）
    if (__j == begin())     
      return pair<iterator,bool>(_M_insert(__x, __y, __v), true);
    else
      --__j;
  if (_M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__v)))
    return pair<iterator,bool>(_M_insert(__x, __y, __v), true);
  return pair<iterator,bool>(__j, false);
}

//             插入不相等的值 指定的位置？？？ 自动排序吗 这个位置？？
template <class _Key, class _Val, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator 
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>
  ::insert_unique(iterator __position, const _Val& __v)
{
  if (__position._M_node == _M_header->_M_left)
   { // begin()
    if (size() > 0 && 
        _M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node)))
      return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    else
      return insert_unique(__v).first;
  }
   else if (__position._M_node == _M_header)
   { // end()
    if (_M_key_compare(_S_key(_M_rightmost()), _KeyOfValue()(__v)))
      return _M_insert(0, _M_rightmost(), __v);
    else
      return insert_unique(__v).first;
  } 
  else
   {
    iterator __before = __position;
    --__before;
    if (_M_key_compare(_S_key(__before._M_node), _KeyOfValue()(__v)) 
        && _M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node))) {
      if (_S_right(__before._M_node) == 0)
        return _M_insert(0, __before._M_node, __v); 
      else
        return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    } else
      return insert_unique(__v).first;
  }
}
//            插入相等的值
template <class _Key, class _Val, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>
  ::insert_equal(iterator __position, const _Val& __v)
{
  if (__position._M_node == _M_header->_M_left) { // begin()
    if (size() > 0 && 
        !_M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)))
      return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    else
      return insert_equal(__v);
  } else if (__position._M_node == _M_header) {// end()
    if (!_M_key_compare(_KeyOfValue()(__v), _S_key(_M_rightmost())))
      return _M_insert(0, _M_rightmost(), __v);
    else
      return insert_equal(__v);
  } else {
    iterator __before = __position;
    --__before;
    if (!_M_key_compare(_KeyOfValue()(__v), _S_key(__before._M_node))
        && !_M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v))) {
      if (_S_right(__before._M_node) == 0)
        return _M_insert(0, __before._M_node, __v); 
      else
        return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    } else
      return insert_equal(__v);
  }
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
void
_Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_equal(const _Val* __first, const _Val* __last)
{
  for ( ; __first != __last; ++__first)
    insert_equal(*__first);
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
void
_Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_equal(const_iterator __first, const_iterator __last)
{
  for ( ; __first != __last; ++__first)
    insert_equal(*__first);
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
void 
_Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_unique(const _Val* __first, const _Val* __last)
{
  for ( ; __first != __last; ++__first)
    insert_unique(*__first);
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
void _Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_unique(const_iterator __first, const_iterator __last)
{
  for ( ; __first != __last; ++__first)
    insert_unique(*__first);
}

#endif /* __STL_MEMBER_TEMPLATES */
         
template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(iterator __position)
{
  _Link_type __y = 
    (_Link_type) _Rb_tree_rebalance_for_erase(__position._M_node,
                                              _M_header->_M_parent,
                                              _M_header->_M_left,
                                              _M_header->_M_right);
  destroy_node(__y);
  --_M_node_count;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::size_type 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::erase(const _Key& __x)
{
  pair<iterator,iterator> __p = equal_range(__x);
  size_type __n = 0;
  distance(__p.first, __p.second, __n);
  erase(__p.first, __p.second);
  return __n;
}

template <class _Key, class _Val, class _KoV, class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_Link_type 
_Rb_tree<_Key,_Val,_KoV,_Compare,_Alloc>
  ::_M_copy(_Link_type __x, _Link_type __p)
{
                        // structural copy.  __x and __p must be non-null.
  _Link_type __top = _M_clone_node(__x);
  __top->_M_parent = __p;
 
  __STL_TRY {
    if (__x->_M_right)
      __top->_M_right = _M_copy(_S_right(__x), __top);
    __p = __top;
    __x = _S_left(__x);

    while (__x != 0) {
      _Link_type __y = _M_clone_node(__x);
      __p->_M_left = __y;
      __y->_M_parent = __p;
      if (__x->_M_right)
        __y->_M_right = _M_copy(_S_right(__x), __y);
      __p = __y;
      __x = _S_left(__x);
    }
  }
  __STL_UNWIND(_M_erase(__top));

  return __top;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::_M_erase(_Link_type __x)
{
                                // erase without rebalancing
  while (__x != 0) {
    _M_erase(_S_right(__x));
    _Link_type __y = _S_left(__x);
    destroy_node(__x);
    __x = __y;
  }
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(iterator __first, iterator __last)
{
  if (__first == begin() && __last == end())
    clear();
  else
    while (__first != __last) erase(__first++);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(const _Key* __first, const _Key* __last) 
{
  while (__first != __last) erase(*__first++);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::find(const _Key& __k)
{
  _Link_type __y = _M_header;      // Last node which is not less than __k. 
  _Link_type __x = _M_root();      // Current node. 

  while (__x != 0) 
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);

  iterator __j = iterator(__y);   
  return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? 
     end() : __j;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::find(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) {
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);
  }
  const_iterator __j = const_iterator(__y);   
  return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ?
    end() : __j;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::size_type 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::count(const _Key& __k) const
{
  pair<const_iterator, const_iterator> __p = equal_range(__k);
  size_type __n = 0;
  distance(__p.first, __p.second, __n);
  return __n;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::lower_bound(const _Key& __k)
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) 
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);

  return iterator(__y);
}
//前驱结点
template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::lower_bound(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) 
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);

  return const_iterator(__y);
}
//后继结点
template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::upper_bound(const _Key& __k)
{
  _Link_type __y = _M_header; /* Last node which is greater than __k. */
  _Link_type __x = _M_root(); /* Current node. */

   while (__x != 0) 
     if (_M_key_compare(__k, _S_key(__x)))
       __y = __x, __x = _S_left(__x);
     else
       __x = _S_right(__x);

   return iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::upper_bound(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is greater than __k. */
  _Link_type __x = _M_root(); /* Current node. */

   while (__x != 0) 
     if (_M_key_compare(__k, _S_key(__x)))
       __y = __x, __x = _S_left(__x);
     else
       __x = _S_right(__x);

   return const_iterator(__y);
}
//范围
template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
pair<typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator,
     typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator>
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::equal_range(const _Key& __k)
{
  return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
}

template <class _Key, class _Value, class _KoV, class _Compare, class _Alloc>
pair<typename _Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::const_iterator,
     typename _Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::const_iterator>
_Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>
  ::equal_range(const _Key& __k) const
{
  return pair<const_iterator,const_iterator>(lower_bound(__k),
                                             upper_bound(__k));
}

inline int 
__black_count(_Rb_tree_node_base* __node, _Rb_tree_node_base* __root)
{
  if (__node == 0)
    return 0;
  else {
    int __bc = __node->_M_color == _S_rb_tree_black ? 1 : 0;
    if (__node == __root)
      return __bc;
    else
      return __bc + __black_count(__node->_M_parent, __root);
  }
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
bool _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::__rb_verify() const
{
  if (_M_node_count == 0 || begin() == end())
    return _M_node_count == 0 && begin() == end() &&
      _M_header->_M_left == _M_header && _M_header->_M_right == _M_header;
  
  int __len = __black_count(_M_leftmost(), _M_root());
  for (const_iterator __it = begin(); __it != end(); ++__it) {
    _Link_type __x = (_Link_type) __it._M_node;
    _Link_type __L = _S_left(__x);
    _Link_type __R = _S_right(__x);

    if (__x->_M_color == _S_rb_tree_red)
      if ((__L && __L->_M_color == _S_rb_tree_red) ||
          (__R && __R->_M_color == _S_rb_tree_red))
        return false;

    if (__L && _M_key_compare(_S_key(__x), _S_key(__L)))
      return false;
    if (__R && _M_key_compare(_S_key(__R), _S_key(__x)))
      return false;

    if (!__L && !__R && __black_count(__x, _M_root()) != __len)
      return false;
  }

  if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
    return false;
  if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
    return false;

  return true;
}

// Class rb_tree is not part of the C++ standard.  It is provided for
// compatibility with the HP STL.

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          class _Alloc = __STL_DEFAULT_ALLOCATOR(_Value) >
struct rb_tree : public _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>
{
  typedef _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> _Base;
  typedef typename _Base::allocator_type allocator_type;

  rb_tree(const _Compare& __comp = _Compare(),
          const allocator_type& __a = allocator_type())
    : _Base(__comp, __a) {}
  
  ~rb_tree() {}
};
