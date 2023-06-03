template <class _Tp, class _Alloc>
//__position位置 __n 插入的数量   __x 插入的具体的数值
void vector<_Tp, _Alloc>::_M_fill_insert(iterator __position, size_type __n, 
                                         const _Tp& __x)
{
  if (__n != 0) { //必须插入一定数量的值
        //插入有可能内存不足需提前进行大小判断  这个空间完全足够的情况下
    if (size_type(_M_end_of_storage - _M_finish) >= __n) {
      _Tp __x_copy = __x;
      const size_type __elems_after = _M_finish - __position;//计算插入点之后的现有元素个数
      iterator __old_finish = _M_finish;
      if (__elems_after > __n) {
          //插入点之后的现有元素个数“大于”新增的元素个数
        uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
        _M_finish += __n;//这时候已经可以知道尾迭代器的位置
        copy_backward(__position, __old_finish - __n, __old_finish);
        fill(__position, __position + __n, __x_copy);
      }
      else {
        //插入点之后的现有元素个数“小于等于”新增元素个数
        //分两部分移动 先把旧的n个位置的元素移出去，再把新元素移进来，再把n个新元素之后的位置的值在移到后面去
        uninitialized_fill_n(_M_finish, __n - __elems_after, __x_copy);
        _M_finish += __n - __elems_after;
        uninitialized_copy(__position, __old_finish, _M_finish);
        _M_finish += __elems_after;
        fill(__position, __old_finish, __x_copy);
      }
    }
    else {
      //这是目前空间不足的情况下 配置额外的内存
        //首先决定新长度:旧长度的两倍，或旧长度+新增元素的个数 
      const size_type __old_size = size();        
      const size_type __len = __old_size + max(__old_size, __n);
      iterator __new_start = _M_allocate(__len);
      iterator __new_finish = __new_start;
      __STL_TRY {
          //一下首先将旧vector的插入点之前的元素复制到新空间
        __new_finish = uninitialized_copy(_M_start, __position, __new_start);
         //一下再将新增元素填入新空间
        __new_finish = uninitialized_fill_n(__new_finish, __n, __x);
        //以下再将旧vector的插入点之后的复制新空间
        __new_finish= uninitialized_copy(__position, _M_finish, __new_finish);
      }
      __STL_UNWIND((destroy(__new_start,__new_finish), 
                    _M_deallocate(__new_start,__len)));
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = __new_start;
      _M_finish = __new_finish;
      _M_end_of_storage = __new_start + __len;
    }
  }
}
