template <class _Tp, class _Alloc> 
class _Vector_base {
public:
  //嵌套型别定义
  typedef _Tp value_type;
  typedef value_type* pointer;;//
  typedef value_type* iterator;;//
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
protected:
  _Tp* _M_start;
  _Tp* _M_finish;//最后一个数据的位置
  _Tp* _M_end_of_storage;//申请内存的末尾位置

  typedef simple_alloc<_Tp, _Alloc> _M_data_allocator;
  void _M_insert_aux(iterator __position, const _Tp& __x);

public:
// ----------vector基本功能相关-----
  iterator begin() { return _M_start; }
  const_iterator begin() const { return _M_start; }
  iterator end() { return _M_finish; } //这个end指向的是末尾元素的下一个，及有可能为空
  const_iterator end() const { return _M_finish; }

  reverse_iterator rbegin()
    { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const
    { return const_reverse_iterator(end()); }
  reverse_iterator rend()
    { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

  size_type size() const //存数据量的大小
    { return size_type(end() - begin()); }
  size_type max_size() const  //这个是？？
    { return size_type(-1) / sizeof(_Tp); }
  size_type capacity() const //能够存的数据的容量，
    { return size_type(_M_end_of_storage - begin()); }
  bool empty() const
    { return begin() == end(); } //妙
  //    begin() + __n 再取里面的值 加*号
  reference operator[](size_type __n) { return *(begin() + __n); }
  const_reference operator[](size_type __n) const { return *(begin() + __n); }
    //-----------构造函数相关--------------
  explicit vector(const allocator_type& __a = allocator_type())
    : _Base(__a) {}

  vector(size_type __n, const _Tp& __value,
         const allocator_type& __a = allocator_type()) 
    : _Base(__n, __a)
    { _M_finish = uninitialized_fill_n(_M_start, __n, __value); }

  explicit vector(size_type __n)
    : _Base(__n, allocator_type())
    { _M_finish = uninitialized_fill_n(_M_start, __n, _Tp()); }

  vector(const vector<_Tp, _Alloc>& __x) 
    : _Base(__x.size(), __x.get_allocator())
    { _M_finish = uninitialized_copy(__x.begin(), __x.end(), _M_start); }
     ~vector() { destroy(_M_start, _M_finish); }
//--------------------------------------------------------------
 reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  void push_back(const _Tp& __x) {
    if (_M_finish != _M_end_of_storage) {
      construct(_M_finish, __x);//添加值
      ++_M_finish;
    }
    else
    //原有的内存不足，此时需要扩容
      _M_insert_aux(end(), __x);
      
  }
  void push_back() {
    if (_M_finish != _M_end_of_storage) {
      construct(_M_finish);
      ++_M_finish;
    }
    else
      _M_insert_aux(end());
  }
  void swap(vector<_Tp, _Alloc>& __x) {
    __STD::swap(_M_start, __x._M_start);
    __STD::swap(_M_finish, __x._M_finish);
    __STD::swap(_M_end_of_storage, __x._M_end_of_storage);
  }

  iterator insert(iterator __position, const _Tp& __x) {
    size_type __n = __position - begin();
    //这个__position == end()再空间足够的情况下，最后一个空位置添加，不需要任何拷贝操作

    if (_M_finish != _M_end_of_storage && __position == end()) {
      construct(_M_finish, __x);
      ++_M_finish;//位置++
    }
    else
    //这个可能有内存不足，插入位置处在vector中间，需要所有插入点的位置的值向后
    //移动并拷贝。
      _M_insert_aux(__position, __x);
    return begin() + __n;
  }
  iterator insert(iterator __position) {
    size_type __n = __position - begin();
    if (_M_finish != _M_end_of_storage && __position == end()) {
      construct(_M_finish);//
      ++_M_finish;
    }
    else
      _M_insert_aux(__position);//这个内存重新分配也会导致begin()发生改变
    return begin() + __n;//返回迭代器的位置所以这里需要begin+n 而不是_M_finish++；
  }

  //取出末尾的元素，也就是end的前一个元素
  void pop_back() {
    --_M_finish;//这个必须要-- 
    destroy(_M_finish);
  }
  iterator erase(iterator __position) {
    if (__position + 1 != end())
    {
      //删除__position位置上的值之后，后面所有的值需要向前进一个单位，那么末尾的迭代器的位置也许减一
      copy(__position + 1, _M_finish, __position);//采用覆盖的方式
    }
    --_M_finish;
    destroy(_M_finish); //所以最后一个值需要单独删除
    return __position;
  }
  //删除[__first,__last)
  iterator erase(iterator __first, iterator __last) {
    //清除实际上就是将__last之后的数据按序复制到first后的位置序列上 返回一个复制之后的最后一个新的伪位置
    iterator __i = copy(__last, _M_finish, __first);
    destroy(__i, _M_finish);//真正清除后序多余空间的元素，
    _M_finish = _M_finish - (__last - __first);//调整_M_finish位置的值
    return __first;
  }

  void resize(size_type __new_size, const _Tp& __x) {
    if (__new_size < size()) 
      erase(begin() + __new_size, end());
    else
      insert(end(), __new_size - size(), __x);
  }
  void resize(size_type __new_size) { resize(__new_size, _Tp()); }
  void clear() { erase(begin(), end()); }


template <class _Tp, class _Alloc>
void 
vector<_Tp, _Alloc>::_M_insert_aux(iterator __position, const _Tp& __x)
{
  //空间足够的情况下，
  if (_M_finish != _M_end_of_storage) {
    construct(_M_finish, *(_M_finish - 1));
    ++_M_finish;
    _Tp __x_copy = __x;
    copy_backward(__position, _M_finish - 2, _M_finish - 1);
    *__position = __x_copy;
  }
  else {
    //这时空间不够的情况下
    const size_type __old_size = size();
    const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
    iterator __new_start = _M_allocate(__len);
    iterator __new_finish = __new_start;
    //异常判断，就是为了防止新空间分配可能出现问题，保证时强异常安全的
    __STL_TRY {
      __new_finish = uninitialized_copy(_M_start, __position, __new_start);
      construct(__new_finish, __x);
      ++__new_finish;
      __new_finish = uninitialized_copy(__position, _M_finish, __new_finish);
    }
    //摧毁旧的空间，
    __STL_UNWIND((destroy(__new_start,__new_finish), 
                  _M_deallocate(__new_start,__len)));
    destroy(begin(), end());

    _M_deallocate(_M_start, _M_end_of_storage - _M_start);
    //新迭代器的位置更新
    _M_start = __new_start;
    _M_finish = __new_finish;
    _M_end_of_storage = __new_start + __len;
  }
}



//---------------运算符重载---------------
template <class _Tp, class _Alloc>
inline bool 
operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
{
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Tp, class _Alloc>
inline bool 
operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
{
  return lexicographical_compare(__x.begin(), __x.end(), 
                                 __y.begin(), __y.end());
}

//-------------------------------------------------------------


