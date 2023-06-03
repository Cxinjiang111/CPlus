/*让我们思考一下，deque迭代器应该具备什么结构。首先，它必须能够指出分段连续空间（亦即缓冲区）在哪里，
其次它必须能够判断自己是否已经处于其所 在缓冲区的边缘，如果是， 
一旦前进或后退时就必须跳跃至下一个或上一个缓冲区。为了能够正确跳跃，
deque必须随时掌握管控中心(map)。下面这种实现方式符合需求：*/
#include<iostream>
template<class T,class Ref,class Ptr,size_t BufSize>
struct __deque_iterator{
    typedef __deque_iterator<T,T&,T*,BufSize> iterator;
    typedef __deque_iterator<T,const T&,const T*,BufSize>const_iterator;
    //用来决定缓冲区大小的函数buffer_size 调用全局函数__deque_buf_size
    //如果n不为0，传回n，表示buffer size 使用默认值，那么
    //如果sz小于512，传回512/sz，如果sz不小于512，传回1
    static size_tb buffer_size(){return __deque_buf_size(BufSize,sizeof(T));}

    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T** map_pointer;

    typedef __deque_iterator self;
    T*cur;  //迭代器所指之物缓冲区钟的现行元素
    T*first;//迭代器所指之物缓冲区的头
    T*last; //迭代器所指之物缓冲区的尾

    iterator start;//指向第一个结点的第一个元素值的指针
    iterator finish;//指向最后一个结点的最后一个元素的位置

    map_pointer node;
    //一旦行进时遇到缓冲区边缘，可能需要调用set_node()跳出一个缓冲区
    void set_node(map_pointer new_node){
        node=new_node;
        first=*new_node;
        last=first+difference_type(buffer_size());
    }
    reference operator*()const{return *cur;}
    pointer operator->()const{return &(operator*());}


    difference_type operator-(const self &x)const{
    //difference_type(buffer_size())*(node-x.node-1)排列相差的结点数所差的内存数量
    //(cur-first)自身还有多少个内存区域，x.last-x.cur x还有多少个内存区域
        return difference_type(buffer_size())*(node-x.node-1)+
            (cur-first)+(x.last-x.cur);
    }

  _Self& operator++() {
    ++_M_cur; 切换到下一个元素
    if (_M_cur == _M_last) {    //如果已达所在缓冲区的尾端
      _M_set_node(_M_node + 1); //就切换到下一个结点的第一个元素
      _M_cur = _M_first;    
    }
    return *this; 
  }
  _Self operator++(int)  {
    _Self __tmp = *this;
    ++*this;
    return __tmp;
  }

  _Self& operator--() {
    if (_M_cur == _M_first) {//如果已达所在缓冲区的首端
      _M_set_node(_M_node - 1); //就切换到下一个结点的最后一个元素
      _M_cur = _M_last;
    }
    --_M_cur;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    --*this;
    return __tmp;
  }

  _Self& operator+=(difference_type __n)
  {
    //总的内存在deque中的内存偏移位置
    difference_type __offset = __n + (_M_cur - _M_first);
    //首先需要判断是否跳出一个缓冲区
    if (__offset >= 0 && __offset < difference_type(_S_buffer_size()))
        //在缓冲区内部
      _M_cur += __n;
    else {
        //标的位置需要跨缓冲区
        // __offset / difference_type(_S_buffer_size())需要跨的缓冲区个数 结点的偏移个数
      difference_type __node_offset =
        __offset > 0 ? __offset / difference_type(_S_buffer_size())
                   : -difference_type((-__offset - 1) / _S_buffer_size()) - 1;
      _M_set_node(_M_node + __node_offset);//寻找偏移后结点的位置
      //在跨过结点的缓冲区内指向元素的位置 返回具体指向元素的指针值
      _M_cur = _M_first + 
        (__offset - __node_offset * difference_type(_S_buffer_size()));
    }
    return *this;
  }

  _Self operator+(difference_type __n) const
  {
    _Self __tmp = *this;
    return __tmp += __n;
  }

  _Self& operator-=(difference_type __n) { return *this += -__n; }
 
  _Self operator-(difference_type __n) const {
    _Self __tmp = *this;
    return __tmp -= __n;
  }

  reference operator[](difference_type __n) const { return *(*this + __n); }

  bool operator==(const _Self& __x) const { return _M_cur == __x._M_cur; }
  bool operator!=(const _Self& __x) const { return !(*this == __x); }
  bool operator<(const _Self& __x) const {
    return (_M_node == __x._M_node) ? 
      (_M_cur < __x._M_cur) : (_M_node < __x._M_node);
  }
  bool operator>(const _Self& __x) const  { return __x < *this; }
  bool operator<=(const _Self& __x) const { return !(__x < *this); }
  bool operator>=(const _Self& __x) const { return !(*this < __x); }

};
__deque_buf_size(size_t n,size_t sz){
    return n!=0? n:(sz<512?(512/sz):size_t(1));

  iterator begin() { return _M_start; }
  iterator end() { return _M_finish; }
  const_iterator begin() const { return _M_start; }
  const_iterator end() const { return _M_finish; }

  reverse_iterator rbegin() { return reverse_iterator(_M_finish); }
  reverse_iterator rend() { return reverse_iterator(_M_start); }
  const_reverse_iterator rbegin() const 
    { return const_reverse_iterator(_M_finish); }
  const_reverse_iterator rend() const 
    { return const_reverse_iterator(_M_start); }

  reference operator[](size_type __n)
    { return _M_start[difference_type(__n)]; }
  const_reference operator[](size_type __n) const 
    { return _M_start[difference_type(__n)]; }



    reference front() { return *_M_start; }
    reference back() {
        iterator __tmp = _M_finish;
        --__tmp;
        return *__tmp;
    }
    const_reference front() const { return *_M_start; }
    const_reference back() const {
        const_iterator __tmp = _M_finish;
        --__tmp;
        return *__tmp;
    }

    size_type size() const { return _M_finish - _M_start; }
    size_type max_size() const { return size_type(-1); }
    bool empty() const { return _M_finish == _M_start; }




}

