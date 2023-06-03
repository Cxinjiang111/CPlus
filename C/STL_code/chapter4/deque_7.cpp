//deque的最终状态（无任何元素时）保有一个缓冲区，clear（）完成之后回复到初始状态，也同样要保留一个缓冲区

template <class _Tp, class _Alloc> 
void deque<_Tp,_Alloc>::clear()
{
    //这里 遍历头是_M_start._M_node + 1 尾是_M_finish._M_node的前一个 怕只有一种结点，那么有可能释放掉全部，而按要求是哪怕无元素也要保留一个结点
  for (_Map_pointer __node = _M_start._M_node + 1;__node < _M_finish._M_node;++__node)
    { //遍历结点 
    destroy(*__node, *__node + _S_buffer_size());//释放每个结点所指的缓冲区
    _M_deallocate_node(*__node);//释放该结点
  }
    //至少有头尾两个缓冲区 为什么for循环没有删除掉头尾两个缓冲区呢
  if (_M_start._M_node != _M_finish._M_node) {
    destroy(_M_start._M_cur, _M_start._M_last);//将头缓冲区的目前所有元素析构
    destroy(_M_finish._M_first, _M_finish._M_cur);//将尾缓冲区的目前元素析构
    //以下释放尾缓冲区，头缓冲区保留
    _M_deallocate_node(_M_finish._M_first);
  }
  else
   //只有一个缓冲区，将此唯一缓冲区的所有元素析构
    destroy(_M_start._M_cur, _M_finish._M_cur);
    //注意，并不释放缓冲区空间，这唯一的缓冲区将保留
  _M_finish = _M_start;
}
//     用来清除某个元素
//清除pos所指的元素，pos为清除点 清除之后依然保证连续空间的数据存储
 iterator erase(iterator __pos) {
    iterator __next = __pos;
    ++__next;
    difference_type __index = __pos - _M_start;//清除点之前的元素个数
    //如果清除点之前的元素比较少就移动清除点之前的元素
    if (size_type(__index) < (this->size() >> 1)) { 
      copy_backward(_M_start, __pos, __next);//元素向后移动
      pop_front();//移动完毕，最前一个元素冗余，去除
    }
    else {
      copy(__next, _M_finish, __pos);
      pop_back();
    }
    return _M_start + __index;
  }

//删除某个区间内的元素[first, last)
template <class _Tp, class _Alloc>
typename deque<_Tp,_Alloc>::iterator 
deque<_Tp,_Alloc>::erase(iterator __first, iterator __last)
{
    //清除整个空间
  if (__first == _M_start && __last == _M_finish) {
    clear();
    return _M_finish;
  }
  else {
    difference_type __n = __last - __first;//删除的空间长度
    difference_type __elems_before = __first - _M_start;//首元素之前还存有的空间，
    if (__elems_before < difference_type((this->size() - __n) / 2)) {//如果前方的元素较少，
      copy_backward(_M_start, __first, __last);//向后移动前方元素（覆盖清除区间）
      iterator __new_start = _M_start + __n; //此时标记deque的新起点
      destroy(_M_start, __new_start); //移动完毕，将冗余的元素析构
      //将荣誉的缓冲区释放
      _M_destroy_nodes(__new_start._M_node, _M_start._M_node);
      _M_start = __new_start; //设定deque的新起点
    }
    else { //如果清除区间后方的元素比较少
      copy(__last, _M_finish, __first);//向前移动后方元素（覆盖清除区间）
      iterator __new_finish = _M_finish - __n;//此时标记deque的新尾点
      destroy(__new_finish, _M_finish);
      _M_destroy_nodes(__new_finish._M_node + 1, _M_finish._M_node + 1);
      _M_finish = __new_finish;
    }
    return _M_start + __elems_before;
  }
}