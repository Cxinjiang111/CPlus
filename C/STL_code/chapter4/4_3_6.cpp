 void transfer(iterator __position, iterator __first, iterator __last) {
    if (__position != __last) {
      // Remove [first, last) from its old position.
      __last._M_node->_M_prev->_M_next     = __position._M_node;
      __first._M_node->_M_prev->_M_next    = __last._M_node;
      __position._M_node->_M_prev->_M_next = __first._M_node; 

      // Splice [first, last) into its new position.
      _List_node_base* __tmp      = __position._M_node->_M_prev;
      __position._M_node->_M_prev = __last._M_node->_M_prev;
      __last._M_node->_M_prev     = __first._M_node->_M_prev; 
      __first._M_node->_M_prev    = __tmp;
    }
  }

public:
  void splice(iterator __position, list& __x) {
    if (!__x.empty()) 
      this->transfer(__position, __x.begin(), __x.end());
  }
  void splice(iterator __position, list&, iterator __i) {
    iterator __j = __i;
    ++__j;
    if (__position == __i || __position == __j) return;
    this->transfer(__position, __i, __j);
  }
  void splice(iterator __position, list&, iterator __first, iterator __last) {
    if (__first != __last) 
      this->transfer(__position, __first, __last);
  }
  void remove(const _Tp& __value);
  void unique();
  void merge(list& __x);
  void reverse();
  void sort();


  
template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::remove(const _Tp& __value)
{
  iterator __first = begin();
  iterator __last = end();
  while (__first != __last) {
    iterator __next = __first;
    ++__next;
    if (*__first == __value) erase(__first);
    __first = __next;
  }
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::unique()
{
  iterator __first = begin();
  iterator __last = end();
  if (__first == __last) return;
  iterator __next = __first;
  while (++__next != __last) {
    if (*__first == *__next)
      erase(__next);
    else
      __first = __next;
    __next = __first;
  }
}

template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::merge(list<_Tp, _Alloc>& __x)
{
  iterator __first1 = begin();
  iterator __last1 = end();
  iterator __first2 = __x.begin();
  iterator __last2 = __x.end();
  while (__first1 != __last1 && __first2 != __last2)
    if (*__first2 < *__first1) {
      iterator __next = __first2;
      transfer(__first1, __first2, ++__next);
      __first2 = __next;
    }
    else
      ++__first1;
  if (__first2 != __last2) transfer(__last1, __first2, __last2);
}

//list不能使用STL算法必须使用自己的sort（）member function STL算法只接受ＲａｎｄｏｍAccessIteratｏｒ 
template <class _Tp, class _Alloc>
void list<_Tp, _Alloc>::sort()
{
  // Do nothing if the list has length 0 or 1.
  if (_M_node->_M_next != _M_node && _M_node->_M_next->_M_next != _M_node) {
    ／／一些新的ｌｉｓｔｓ作为中介数据存放区
    list<_Tp, _Alloc> __carry;
    list<_Tp, _Alloc> __counter[64];
    int __fill = 0;
    while (!empty()) {
      __carry.splice(__carry.begin(), *this, begin());
      int __i = 0;
      while(__i < __fill && !__counter[__i].empty()) {
        __counter[__i].merge(__carry);
        __carry.swap(__counter[__i++]);
      }
      __carry.swap(__counter[__i]);         
      if (__i == __fill) ++__fill;
    } 

    for (int __i = 1; __i < __fill; ++__i)
      __counter[__i].merge(__counter[__i-1]);
    swap(__counter[__fill-1]);
  }
}

inline void __List_base_reverse(_List_node_base* __p)
{
  _List_node_base* __tmp = __p;
  do {
    __STD::swap(__tmp->_M_next, __tmp->_M_prev);
    __tmp = __tmp->_M_prev;     // Old next node is now prev.
  } while (__tmp != __p);
}