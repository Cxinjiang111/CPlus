/*


*/
template<class RandomAccessIterator>
void sort_heap(RandomAccessIterator first,RandomAccessIterator last){
    while(last-first>1){ 
        //每次循环一次 只能排序一个值，复杂度为N(logN)
        pop_heap(first,last--);//first 在 内部子调整
    }
}
//-------------------make_heap----------------

template <class _RandomAccessIterator>
inline void  make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
  __STL_REQUIRES(_RandomAccessIterator, _Mutable_RandomAccessIterator);
  __STL_REQUIRES(typename iterator_traits<_RandomAccessIterator>::value_type,
                 _LessThanComparable);
  __make_heap(__first, __last,
              __VALUE_TYPE(__first), __DISTANCE_TYPE(__first));
}
//这个还是有点不太懂？？？？？
template <class _RandomAccessIterator, class _Compare,
          class _Tp, class _Distance>
void __make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
            _Compare __comp, _Tp*, _Distance*)
{
  if (__last - __first < 2) return;//只有一个元素 那就返回
  _Distance __len = __last - __first;
  _Distance __parent = (__len - 2)/2;//取任意迭代器的中间索引，大根堆的话，左边的都比这个索引值处的值大，
    
  while (true) {
      //重排以parent为首的子树，len是为了让__adjust_heap判断操作范围 
    __adjust_heap(__first, __parent, __len, _Tp(*(__first + __parent)),__comp);//自排序中 __comp 可以规定大根堆还是小根堆
    if (__parent == 0) return;
    __parent--;
  }
}

template <class _RandomAccessIterator, class _Compare>
inline void make_heap(_RandomAccessIterator __first, 
          _RandomAccessIterator __last, _Compare __comp)
{
  __STL_REQUIRES(_RandomAccessIterator, _Mutable_RandomAccessIterator);
  __make_heap(__first, __last, __comp,
              __VALUE_TYPE(__first), __DISTANCE_TYPE(__first));
}


