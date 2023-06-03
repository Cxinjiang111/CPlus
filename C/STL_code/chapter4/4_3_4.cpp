template <class _Tp, class _Alloc>
class _List_base 
{
protected:
    //专属之空间配置器，每次配置一个结点大小
  typedef simple_alloc<_List_node<_Tp>, _Alloc> _Alloc_type;
  //配置一个结点并传回  allocate
  _List_node<_Tp>* _M_get_node() { return _Alloc_type::allocate(1); }
  //释放一个结点  deallocate
  void _M_put_node(_List_node<_Tp>* __p) { _Alloc_type::deallocate(__p, 1); } 

//产生（配置并构造）一个结点，带有元素值
  _Node* _M_create_node(const _Tp& __x)
  {
    _Node* __p = _M_get_node();
    __STL_TRY {
      _Construct(&__p->_M_data, __x);
    }
    __STL_UNWIND(_M_put_node(__p));
    return __p;
  }
//销毁（析构并释放）一个结点
void destroy_node(link_type p){
    destroy(&p->data);
    _M_put_node(p);
}
 
};