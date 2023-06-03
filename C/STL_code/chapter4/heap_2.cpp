//--------------------------pop-------------------------
/*
pop操作的结果应为底部容器的第一个元素，因此，首先设定调整值为尾值，然后将首值
调至尾节点，然后调整[first,last-1),使之重新成一个合格的heap
*/

//pop 其实只能pop根结点，因为最后一个结点是我们很难确定的一个值 左右子节点没有严格区分大小
template <class _RandomAccessIterator, class _Tp, class _Distance>
inline void  __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
           _RandomAccessIterator __result, _Tp __value, _Distance*)
{
    //将取出的值记录下来，然后在调整堆结构
  *__result = *__first;//设定发尾值尾首值，于是尾值即为欲求结果，可有客服端稍后再以底层容器之pop_back()取出尾值
  __adjust_heap(__first, _Distance(0), _Distance(__last - __first), __value);
//以上调整heap 洞号为0，欲调整值value
}

template <class _RandomAccessIterator, class _Tp>
inline void 
__pop_heap_aux(_RandomAccessIterator __first, _RandomAccessIterator __last,
               _Tp*)
{
  __pop_heap(__first, __last - 1, __last - 1, 
             _Tp(*(__last - 1)), __DISTANCE_TYPE(__first));
}


template <class _RandomAccessIterator, class _Distance, class _Tp, class _Compare>
void __adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex, _Distance __len, _Tp __value, _Compare __comp)
{
  _Distance __topIndex = __holeIndex;
  _Distance __secondChild = 2 * __holeIndex + 2;//右子结点
  while (__secondChild < __len) {  
    //比较左右子节点的两个值，然后以 __secondChild代表较大子节点
    if (__comp(*(__first + __secondChild), *(__first + (__secondChild - 1))))
      __secondChild--;
    *(__first + __holeIndex) = *(__first + __secondChild);
    __holeIndex = __secondChild;//令较大子值为洞值，在令洞号下移至较大子结点处
    __secondChild = 2 * (__secondChild + 1);//找出新洞结点的右子结点
  }


  if (__secondChild == __len) {//没有右子结点，只有左子结点
     //令左子节点为洞值，在令洞号下移至左子结点处
    *(__first + __holeIndex) = *(__first + (__secondChild - 1));
    __holeIndex = __secondChild - 1;
  }
  __push_heap(__first, __holeIndex, __topIndex, __value, __comp);
}
