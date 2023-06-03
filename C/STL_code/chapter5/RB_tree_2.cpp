//基层迭代器 提供常用迭代器需要的东西，比如常用的运算符++ --，以及指针操作符，解引用，
struct _Rb_tree_base_iterator
{
  typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  _Base_ptr _M_node;
    void _M_increment(int n){ operator +(int)
        for(int i=0;i<n;i++){
             void _M_increment();
        }
    }
//后驱结点 相当于有序数组中的下一位
  void _M_increment()
  {
    //右结点不为空，紧挨着且比自身大的值坑定在自己有孩子中，
    /* 
        \(node) 右节点存在
        /
       /
      /
     /(res)
    */
    if (_M_node->_M_right != 0) {
      _M_node = _M_node->_M_right;
      while (_M_node->_M_left != 0)
        _M_node = _M_node->_M_left;
    }
    else {//如果右节点为空，结果只能在父结点中寻找，如果自己的叔叔结点不存在最小值中寻找
      //寻找父节点
      /*      
            /(res)  
           \
  while     \node   右节点不存在，只能自己作为res的前驱结点来反向考虑这个问题
            /\(null)   
           /
      */
      _Base_ptr __y = _M_node->_M_parent;
      while (_M_node == __y->_M_right) {
        _M_node = __y;
        __y = __y->_M_parent;
      }
      //
      if (_M_node->_M_right != __y)
        _M_node = __y;
    }
  }

  void _M_decrement()
  {
    if (_M_node->_M_color == _S_rb_tree_red &&
        _M_node->_M_parent->_M_parent == _M_node)
      _M_node = _M_node->_M_right;
    else if (_M_node->_M_left != 0) {
      _Base_ptr __y = _M_node->_M_left;
      while (__y->_M_right != 0)
        __y = __y->_M_right;
      _M_node = __y;
    }
    else {
      _Base_ptr __y = _M_node->_M_parent;
      while (_M_node == __y->_M_left) {
        _M_node = __y;
        __y = __y->_M_parent;
      }
      _M_node = __y;
    }
  }
};

