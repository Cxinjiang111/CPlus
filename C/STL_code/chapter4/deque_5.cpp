
// Called only if _M_finish._M_cur == _M_finish._M_last - 1.
template <class _Tp, class _Alloc>
void deque<_Tp,_Alloc>::_M_push_back_aux(const value_type& __t)
{
  value_type __t_copy = __t;
  _M_reserve_map_at_back();
  *(_M_finish._M_node + 1) = _M_allocate_node();
  __STL_TRY {
    construct(_M_finish._M_cur, __t_copy);
    _M_finish._M_set_node(_M_finish._M_node + 1);
    _M_finish._M_cur = _M_finish._M_first;
  }
  __STL_UNWIND(_M_deallocate_node(*(_M_finish._M_node + 1)));
}

// Called only if _M_finish._M_cur == _M_finish._M_last - 1.
template <class _Tp, class _Alloc>
void deque<_Tp,_Alloc>::_M_push_back_aux()
{
  _M_reserve_map_at_back();
  *(_M_finish._M_node + 1) = _M_allocate_node();
  __STL_TRY {
    construct(_M_finish._M_cur);
    _M_finish._M_set_node(_M_finish._M_node + 1);
    _M_finish._M_cur = _M_finish._M_first;
  }
  __STL_UNWIND(_M_deallocate_node(*(_M_finish._M_node + 1)));
}

// Called only if _M_start._M_cur == _M_start._M_first.
template <class _Tp, class _Alloc>
void  deque<_Tp,_Alloc>::_M_push_front_aux(const value_type& __t)
{
  value_type __t_copy = __t;
  _M_reserve_map_at_front();//若符合某种条件则必须重换一个map 实际需要调用reallocate_map需要重新寻找内存
  *(_M_start._M_node - 1) = _M_allocate_node();//配置一个新结点（缓冲区）
  __STL_TRY {
    _M_start._M_set_node(_M_start._M_node - 1);//改变start，令其指向新结点
    _M_start._M_cur = _M_start._M_last - 1;//改变start的状态 向前移动以为
    construct(_M_start._M_cur, __t_copy);//针对标的元素设值
  }
  __STL_UNWIND((++_M_start, _M_deallocate_node(*(_M_start._M_node - 1)))); //发生异常的话，全部失效
} 

// Called only if _M_start._M_cur == _M_start._M_first.
template <class _Tp, class _Alloc>
void deque<_Tp,_Alloc>::_M_push_front_aux()
{
  _M_reserve_map_at_front();
  *(_M_start._M_node - 1) = _M_allocate_node();
  __STL_TRY {
    _M_start._M_set_node(_M_start._M_node - 1);
    _M_start._M_cur = _M_start._M_last - 1;
    construct(_M_start._M_cur);
  }
  __STL_UNWIND((++_M_start, _M_deallocate_node(*(_M_start._M_node - 1))));
} 

// Called only if _M_finish._M_cur == _M_finish._M_first.
template <class _Tp, class _Alloc>
void deque<_Tp,_Alloc>::_M_pop_back_aux()
{
  _M_deallocate_node(_M_finish._M_first);//释放最后一个缓冲区
  _M_finish._M_set_node(_M_finish._M_node - 1);//尾结点向前移动一位
  _M_finish._M_cur = _M_finish._M_last - 1;//指向的元素指针向前移动一位
  destroy(_M_finish._M_cur); //将该元素析构
}

// Called only if _M_start._M_cur == _M_start._M_last - 1.  Note that 
// if the deque has at least one element (a precondition for this member 
// function), and if _M_start._M_cur == _M_start._M_last, then the deque 
// must have at least two nodes.
template <class _Tp, class _Alloc>
void deque<_Tp,_Alloc>::_M_pop_front_aux()
{
  destroy(_M_start._M_cur);
  _M_deallocate_node(_M_start._M_first);
  _M_start._M_set_node(_M_start._M_node + 1);
  _M_start._M_cur = _M_start._M_first;
}      
