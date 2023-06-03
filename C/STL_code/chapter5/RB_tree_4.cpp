
template <class _Tp, class _Alloc>
struct _Rb_tree_base
{
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Rb_tree_base(const allocator_type&) 
    : _M_header(0) { _M_header = _M_get_node(); }
  ~_Rb_tree_base() { _M_put_node(_M_header); }

protected:
  _Rb_tree_node<_Tp>* _M_header;

  typedef simple_alloc<_Rb_tree_node<_Tp>, _Alloc> _Alloc_type;

  _Rb_tree_node<_Tp>* _M_get_node()
    { return _Alloc_type::allocate(1); }
  void _M_put_node(_Rb_tree_node<_Tp>* __p)
    { _Alloc_type::deallocate(__p, 1); }
};

#endif /* __STL_USE_STD_ALLOCATORS */

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          class _Alloc = __STL_DEFAULT_ALLOCATOR(_Value) >
class _Rb_tree : protected _Rb_tree_base<_Value, _Alloc> {
  typedef _Rb_tree_base<_Value, _Alloc> _Base;
protected:
  typedef _Rb_tree_node_base* _Base_ptr;
  typedef _Rb_tree_node<_Value> _Rb_tree_node;
  typedef _Rb_tree_Color_type _Color_type;
public:
  typedef _Key key_type;
  typedef _Value value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef _Rb_tree_node* _Link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }

protected:
#ifdef __STL_USE_NAMESPACES
  using _Base::_M_get_node;
  using _Base::_M_put_node;
  using _Base::_M_header;
#endif /* __STL_USE_NAMESPACES */

protected:

  _Link_type _M_create_node(const value_type& __x)
  {
    _Link_type __tmp = _M_get_node();
    __STL_TRY {
      construct(&__tmp->_M_value_field, __x);
    }
    __STL_UNWIND(_M_put_node(__tmp));
    return __tmp;
  }

  _Link_type _M_clone_node(_Link_type __x)
  {
    _Link_type __tmp = _M_create_node(__x->_M_value_field);
    __tmp->_M_color = __x->_M_color;
    __tmp->_M_left = 0;
    __tmp->_M_right = 0;
    return __tmp;
  }

  void destroy_node(_Link_type __p)
  {
    destroy(&__p->_M_value_field);
    _M_put_node(__p);
  }

protected:
  size_type _M_node_count; // keeps track of size of tree
  _Compare _M_key_compare;

  _Link_type& _M_root() const 
    { return (_Link_type&) _M_header->_M_parent; }
  _Link_type& _M_leftmost() const 
    { return (_Link_type&) _M_header->_M_left; }
  _Link_type& _M_rightmost() const 
    { return (_Link_type&) _M_header->_M_right; }

  static _Link_type& _S_left(_Link_type __x)
    { return (_Link_type&)(__x->_M_left); }
  static _Link_type& _S_right(_Link_type __x)
    { return (_Link_type&)(__x->_M_right); }
  static _Link_type& _S_parent(_Link_type __x)
    { return (_Link_type&)(__x->_M_parent); }
  static reference _S_value(_Link_type __x)
    { return __x->_M_value_field; }
  static const _Key& _S_key(_Link_type __x)
    { return _KeyOfValue()(_S_value(__x)); }
  static _Color_type& _S_color(_Link_type __x)
    { return (_Color_type&)(__x->_M_color); }

  static _Link_type& _S_left(_Base_ptr __x)
    { return (_Link_type&)(__x->_M_left); }
  static _Link_type& _S_right(_Base_ptr __x)
    { return (_Link_type&)(__x->_M_right); }
  static _Link_type& _S_parent(_Base_ptr __x)
    { return (_Link_type&)(__x->_M_parent); }
  static reference _S_value(_Base_ptr __x)
    { return ((_Link_type)__x)->_M_value_field; }
  static const _Key& _S_key(_Base_ptr __x)
    { return _KeyOfValue()(_S_value(_Link_type(__x)));} 
  static _Color_type& _S_color(_Base_ptr __x)
    { return (_Color_type&)(_Link_type(__x)->_M_color); }

  static _Link_type _S_minimum(_Link_type __x) 
    { return (_Link_type)  _Rb_tree_node_base::_S_minimum(__x); }

  static _Link_type _S_maximum(_Link_type __x)
    { return (_Link_type) _Rb_tree_node_base::_S_maximum(__x); }

public:
  typedef _Rb_tree_iterator<value_type, reference, pointer> iterator;
  typedef _Rb_tree_iterator<value_type, const_reference, const_pointer> 
          const_iterator;

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  typedef reverse_bidirectional_iterator<iterator, value_type, reference,
                                         difference_type>
          reverse_iterator; 
  typedef reverse_bidirectional_iterator<const_iterator, value_type,
                                         const_reference, difference_type>
          const_reverse_iterator;
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */ 

private:
  iterator _M_insert(_Base_ptr __x, _Base_ptr __y, const value_type& __v);
  _Link_type _M_copy(_Link_type __x, _Link_type __p);
  void _M_erase(_Link_type __x);

public:
                                // allocation/deallocation
  _Rb_tree()
    : _Base(allocator_type()), _M_node_count(0), _M_key_compare()
    { _M_empty_initialize(); }

  _Rb_tree(const _Compare& __comp)
    : _Base(allocator_type()), _M_node_count(0), _M_key_compare(__comp) 
    { _M_empty_initialize(); }

  _Rb_tree(const _Compare& __comp, const allocator_type& __a)
    : _Base(__a), _M_node_count(0), _M_key_compare(__comp) 
    { _M_empty_initialize(); }

  _Rb_tree(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x) 
    : _Base(__x.get_allocator()),
      _M_node_count(0), _M_key_compare(__x._M_key_compare)
  { 
    if (__x._M_root() == 0)
      _M_empty_initialize();
    else {
      _S_color(_M_header) = _S_rb_tree_red;
      _M_root() = _M_copy(__x._M_root(), _M_header);
      _M_leftmost() = _S_minimum(_M_root());
      _M_rightmost() = _S_maximum(_M_root());
    }
    _M_node_count = __x._M_node_count;
  }
  ~_Rb_tree() { clear(); }
  _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& 
  operator=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x);

private:
  void _M_empty_initialize() {
    _S_color(_M_header) = _S_rb_tree_red; // used to distinguish header from 
                                          // __root, in iterator.operator++
    _M_root() = 0;
    _M_leftmost() = _M_header;
    _M_rightmost() = _M_header;
  }

public:    
                                // accessors:
  _Compare key_comp() const { return _M_key_compare; }
  iterator begin() { return _M_leftmost(); }
  const_iterator begin() const { return _M_leftmost(); }
  iterator end() { return _M_header; }
  const_iterator end() const { return _M_header; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { 
    return const_reverse_iterator(end()); 
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { 
    return const_reverse_iterator(begin());
  } 
  bool empty() const { return _M_node_count == 0; }
  size_type size() const { return _M_node_count; }
  size_type max_size() const { return size_type(-1); }

  void swap(_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __t) {
    __STD::swap(_M_header, __t._M_header);
    __STD::swap(_M_node_count, __t._M_node_count);
    __STD::swap(_M_key_compare, __t._M_key_compare);
  }
    
public:
                                // insert/erase
  pair<iterator,bool> insert_unique(const value_type& __x);
  iterator insert_equal(const value_type& __x);

  iterator insert_unique(iterator __position, const value_type& __x);
  iterator insert_equal(iterator __position, const value_type& __x);

#ifdef __STL_MEMBER_TEMPLATES  
  template <class _InputIterator>
  void insert_unique(_InputIterator __first, _InputIterator __last);
  template <class _InputIterator>
  void insert_equal(_InputIterator __first, _InputIterator __last);
#else /* __STL_MEMBER_TEMPLATES */
  void insert_unique(const_iterator __first, const_iterator __last);
  void insert_unique(const value_type* __first, const value_type* __last);
  void insert_equal(const_iterator __first, const_iterator __last);
  void insert_equal(const value_type* __first, const value_type* __last);
#endif /* __STL_MEMBER_TEMPLATES */

  void erase(iterator __position);
  size_type erase(const key_type& __x);
  void erase(iterator __first, iterator __last);
  void erase(const key_type* __first, const key_type* __last);
  void clear() {
    if (_M_node_count != 0) {
      _M_erase(_M_root());
      _M_leftmost() = _M_header;
      _M_root() = 0;
      _M_rightmost() = _M_header;
      _M_node_count = 0;
    }
  }      

public:
                                // set operations:
  iterator find(const key_type& __x);
  const_iterator find(const key_type& __x) const;
  size_type count(const key_type& __x) const;
  iterator lower_bound(const key_type& __x);
  const_iterator lower_bound(const key_type& __x) const;
  iterator upper_bound(const key_type& __x);
  const_iterator upper_bound(const key_type& __x) const;
  pair<iterator,iterator> equal_range(const key_type& __x);
  pair<const_iterator, const_iterator> equal_range(const key_type& __x) const;

public:
                                // Debugging.
  bool __rb_verify() const;
};
