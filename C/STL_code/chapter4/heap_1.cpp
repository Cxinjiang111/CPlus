/*  heap
binary heap 就是一种complete binary tree  
完全二叉树没有任何结点漏洞，所以用array来存储结点，
那么当某个结点位于array的i处时，其左子节点必位于array的2*i
右子节点必位于array的2*i+1处，父节点必位于i/2处
max-heap为每个结点的键值大于或等于子节点的键值
min-heap为每个结点的键值小于或等于子节点的键值
*/


template <class _RandomAccessIterator, class _Distance, class _Tp>
inline void 
__push_heap_aux(_RandomAccessIterator __first,
                _RandomAccessIterator __last, _Distance*, _Tp*)
{
  __push_heap(__first, _Distance((__last - __first) - 1), _Distance(0), 
              _Tp(*(__last - 1)));
    //新值必置于底部容器的最尾端，也就是_Tp(*(__last - 1))；
}

template <class _RandomAccessIterator>
inline void 
push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
  __STL_REQUIRES(_RandomAccessIterator, _Mutable_RandomAccessIterator);
  __STL_REQUIRES(typename iterator_traits<_RandomAccessIterator>::value_type,
                 _LessThanComparable);
//此函数被调用时，新元素已置于底部容器的最尾端
  __push_heap_aux(__first, __last,
                  __DISTANCE_TYPE(__first), __VALUE_TYPE(__first));
}
template <class _RandomAccessIterator, class _Distance, class _Tp, 
          class _Compare>
void
__push_heap(_RandomAccessIterator __first, _Distance __holeIndex,
            _Distance __topIndex, _Tp __value, _Compare __comp)
{
  _Distance __parent = (__holeIndex - 1) / 2;
  while (__holeIndex > __topIndex && __comp(*(__first + __parent), __value)) {
      //当尚未达到顶端，且父节点小于新值，
    *(__first + __holeIndex) = *(__first + __parent);// 令洞值为父节点
    __holeIndex = __parent;                 //调整洞号，向上提升至父节点
    __parent = (__holeIndex - 1) / 2;   //新洞的父节点
  }
  *(__first + __holeIndex) = __value;//令洞值为新值，完成插入操作

}

