
//uninitialized_fill_n 能够使我们将内存配置与对象构造行为分离开来
//他会为指定范围内的所有元素设定相同的初值
POD意指PlainOld Data,也就是标量型别(scalartypes)或传统的Cstruct 型别。
POD型别必然拥有trivialctor / dtor /copy/ assignment函数，
因此，我们可以对POD型别采用最有效率的初值填写手法，
而对non-POD型别采取最保险安全的做法：

template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter 
//                      首迭代器        内存大小          内存填充的值
uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp& __x)
{
  return __uninitialized_fill_n(__first, __n, __x, __VALUE_TYPE(__first));
}

template <class _ForwardIter, class _Size, class _Tp, class _Tp1>
inline _ForwardIter 
__uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp& __x, _Tp1*)
{
    //推导是否是POD型，以此来判断选择保险的还是高效的赋值模式
  typedef typename __type_traits<_Tp1>::is_POD_type _Is_POD;
  return __uninitialized_fill_n_aux(__first, __n, __x, _Is_POD());
}

//不是POD模型
template <class _ForwardIter, class _Size, class _Tp>
_ForwardIter
__uninitialized_fill_n_aux(_ForwardIter __first, _Size __n,
                           const _Tp& __x, __false_type)
{
  _ForwardIter __cur = __first;
  __STL_TRY {
    for ( ; __n > 0; --__n, ++__cur)
      _Construct(&*__cur, __x);
    return __cur;
  }
  __STL_UNWIND(_Destroy(__first, __cur));
}
//POD
//如果copyconstrue口on等同于assignment,而且
// destructor是trivial,以下就有效如果是POD刑别，执行流程就会转进到以下函数。
//这是藉由functiontemplate II的参数推导机制而得
template <class Forwarditera七or,class Size, class T> 
inline Forwarditerator 
// Valid if copy construction is equivalent to assignment, and if the
//  destructor is trivial.
// POD 模型 
template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter
__uninitialized_fill_n_aux(_ForwardIter __first, _Size __n,
                           const _Tp& __x, __true_type)

{
  return fill_n(__first, __n, __x);     //调用STL算法
}

