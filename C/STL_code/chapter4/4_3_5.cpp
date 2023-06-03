//default constructor
public:
list() {empty_initialize();}
protected:
    void empty_initialize(){
        node=get_node();
        node->next=node;//头和尾都指向自己 不设元素值
        node->prev=node;
    }
template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
class list : protected _List_base<_Tp, _Alloc> 
{
    public:
    explicit list(const allocator_type& __a = allocator_type()) : _Base(__a) {}

    iterator begin()             { return (_Node*)(_M_node->_M_next); }
    const_iterator begin() const { return (_Node*)(_M_node->_M_next); }

    iterator end()             { return _M_node; }
    const_iterator end() const { return _M_node; }

    reverse_iterator rbegin() 
        { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const 
        { return const_reverse_iterator(end()); }

    reverse_iterator rend()
        { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const
        { return const_reverse_iterator(begin()); }

    bool empty() const { return _M_node->_M_next == _M_node; }
    size_type size() const {
        size_type __result = 0;
        distance(begin(), end(), __result);
        return __result;
    }
    size_type max_size() const { return size_type(-1); }

    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }
    reference back() { return *(--end()); }
    const_reference back() const { return *(--end()); }

    void swap(list<_Tp, _Alloc>& __x) { __STD::swap(_M_node, __x._M_node); }

    iterator insert(iterator __position, const _Tp& __x) {
        _Node* __tmp = _M_create_node(__x);
        __tmp->_M_next = __position._M_node;
        __tmp->_M_prev = __position._M_node->_M_prev;
        __position._M_node->_M_prev->_M_next = __tmp;
        __position._M_node->_M_prev = __tmp;
        return __tmp;
    }
    iterator insert(iterator __position) { return insert(__position, _Tp()); }
    void insert(iterator __pos, size_type __n, const _Tp& __x)
        { _M_fill_insert(__pos, __n, __x); }
    void _M_fill_insert(iterator __pos, size_type __n, const _Tp& __x); 

    void push_front(const _Tp& __x) { insert(begin(), __x); }
    void push_front() {insert(begin());}
    void push_back(const _Tp& __x) { insert(end(), __x); }
    void push_back() {insert(end());}

    iterator erase(iterator __position) {
        _List_node_base* __next_node = __position._M_node->_M_next;
        _List_node_base* __prev_node = __position._M_node->_M_prev;
        _Node* __n = (_Node*) __position._M_node;
        __prev_node->_M_next = __next_node;
        __next_node->_M_prev = __prev_node;
        _Destroy(&__n->_M_data);
        _M_put_node(__n);
        return iterator((_Node*) __next_node);
    }
    iterator erase(iterator __first, iterator __last);
    void clear() { _Base::clear(); }

    void resize(size_type __new_size, const _Tp& __x);
    void resize(size_type __new_size) { this->resize(__new_size, _Tp()); }

    void pop_front() { erase(begin()); }
    void pop_back() { 
        iterator __tmp = end();
        erase(--__tmp);
    }
    list(size_type __n, const _Tp& __value,
        const allocator_type& __a = allocator_type())
        : _Base(__a)
        { insert(begin(), __n, __value); }
    explicit list(size_type __n)
        : _Base(allocator_type())
        { 
            insert(begin(), __n, _Tp()); 
            }
}

