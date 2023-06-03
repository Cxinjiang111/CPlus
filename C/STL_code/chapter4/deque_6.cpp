
  void _M_reserve_map_at_back (size_type __nodes_to_add = 1) {
     //_M_map_size - (_M_finish._M_node - _M_map) 还剩余多少个node空间
    if (__nodes_to_add + 1 > _M_map_size - (_M_finish._M_node - _M_map))//不足，
      _M_reallocate_map(__nodes_to_add, false);
  }

  void _M_reserve_map_at_front (size_type __nodes_to_add = 1) {
    //_M_start._M_node - _M_map _M_start._M_node当前结点的头减去空的deque整体的头，表明头部还剩多少个结点
    if (__nodes_to_add > size_type(_M_start._M_node - _M_map))
      _M_reallocate_map(__nodes_to_add, true);
  }


template <class _Tp, class _Alloc>
void deque<_Tp,_Alloc>::_M_reallocate_map(size_type __nodes_to_add,
                                          bool __add_at_front)
{
   // 已存有的数据的结点有多少个  
  size_type __old_num_nodes = _M_finish._M_node - _M_start._M_node + 1;
  //旧的节点数+需要添加的节点数是多少个，因为可能需要重新寻找内存区域，
  size_type __new_num_nodes = __old_num_nodes + __nodes_to_add;

  _Map_pointer __new_nstart;
  //如果_M_map_size deque总的结点数大于新的已占有的空间数，其实就是不断在头部加，但是finish 却在deque不到一半的位置上
  //这时比较好的办法是，将所有结点后移，为头部空出空间
  if (_M_map_size > 2 * __new_num_nodes) {
    __new_nstart = _M_map + (_M_map_size - __new_num_nodes) / 2 
                     + (__add_at_front ? __nodes_to_add : 0);
    if (__new_nstart < _M_start._M_node)
      copy(_M_start._M_node, _M_finish._M_node + 1, __new_nstart);
    else
      copy_backward(_M_start._M_node, _M_finish._M_node + 1, 
                    __new_nstart + __old_num_nodes);
  }
  else {
    //如果总的已占有的空间超过总空间的50%,最好的办法就是重新寻找内存区域，在拷贝结点过去就行
    size_type __new_map_size = 
      _M_map_size + max(_M_map_size, __nodes_to_add) + 2;

    _Map_pointer __new_map = _M_allocate_map(__new_map_size);//寻找一块大小为__new_map_size的区域
    //这个应该是明确已有的节点数/2 加上需要在前面添加的节点数，那么已占有多少个结点空间数，加上__new_map相对坐标地址就ok了
    __new_nstart = __new_map + (__new_map_size - __new_num_nodes) / 2
                         + (__add_at_front ? __nodes_to_add : 0);
    //把原有的map内容拷贝过来
    copy(_M_start._M_node, _M_finish._M_node + 1, __new_nstart);
    //释放原有map
    _M_deallocate_map(_M_map, _M_map_size);
    //设定新的map的起始地址与大小
    _M_map = __new_map;
    _M_map_size = __new_map_size;
  }
    //重新设定迭代器start和finish
  _M_start._M_set_node(__new_nstart);
  _M_finish._M_set_node(__new_nstart + __old_num_nodes - 1);
}