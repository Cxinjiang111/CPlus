template <class _Value, class _Ref, class _Ptr>
struct _Rb_tree_iterator : public _Rb_tree_base_iterator
{
    //类型别名，用于编译时，类型识别
  typedef _Value value_type;
  typedef _Ref reference;
  typedef _Ptr pointer;
  typedef _Rb_tree_iterator<_Value, _Value&, _Value*>             
    iterator;
  typedef _Rb_tree_iterator<_Value, const _Value&, const _Value*> 
    const_iterator;
  typedef _Rb_tree_iterator<_Value, _Ref, _Ptr>                   
    _Self;
  typedef _Rb_tree_node<_Value>* _Link_type;
    //构造函数
  _Rb_tree_iterator() {}
  _Rb_tree_iterator(_Link_type __x) { _M_node = __x; }
  _Rb_tree_iterator(const iterator& __it) { _M_node = __it._M_node; }
    //取值 value
  reference operator*() const { return _Link_type(_M_node)->_M_value_field; }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */
    //运算符的
  _Self& operator++() { _M_increment(); return *this; }
  _Self operator++(int) {
    _Self __tmp = *this;
    _M_increment();
    return __tmp;
  }
    
  _Self& operator--() { _M_decrement(); return *this; }
  _Self operator--(int) {
    _Self __tmp = *this;
    _M_decrement();
    return __tmp;
  }
};