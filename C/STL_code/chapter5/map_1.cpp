/*
map 的特性是，所有元素都会根据元素的键值自动排序，map的所有元素都是pair
同时拥有实值value和键值（key） pair的第一个元素被视为键值
第二个元素被视为实值 ，map不允许两个元素拥有相同的键值。
stl_pair.h定义如下:
*/
template <class _T1, class _T2>
struct pair {
  typedef _T1 first_type; //public 
  typedef _T2 second_type; //public

  _T1 first;
  _T2 second;
  pair() : first(_T1()), second(_T2()) {}
  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}
};

template <class _T1, class _T2>
inline bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ 
  return __x.first == __y.first && __x.second == __y.second; 
}

template <class _T1, class _T2>
inline bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ 
  return __x.first < __y.first || 
         (!(__y.first < __x.first) && __x.second < __y.second); 
}
template <class _T1, class _T2>
inline pair<_T1, _T2> make_pair(const _T1& __x, const _T2& __y)
{
  return pair<_T1, _T2>(__x, __y);
}
