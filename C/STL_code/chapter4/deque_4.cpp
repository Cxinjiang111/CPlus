//memory 
 
  void push_back(const value_type& __t) {

    if (_M_finish._M_cur != _M_finish._M_last - 1) {
      construct(_M_finish._M_cur, __t);
      ++_M_finish._M_cur;
    }
    else 
      _M_push_back_aux(__t);
  }

  void push_back() {
        //在第一缓冲区尚有备用空间
    if (_M_finish._M_cur != _M_finish._M_last - 1) {
      construct(_M_finish._M_cur);
      ++_M_finish._M_cur;
    }
    else //第一缓冲区已无备空间
      _M_push_back_aux();
  }

  void push_front(const value_type& __t) {
    if (_M_start._M_cur != _M_start._M_first) {
      construct(_M_start._M_cur - 1, __t);
      --_M_start._M_cur;
    }
    else
      _M_push_front_aux(__t);
  }

  void push_front() {
    if (_M_start._M_cur != _M_start._M_first) {
      construct(_M_start._M_cur - 1);
      --_M_start._M_cur;
    }
    else
      _M_push_front_aux();
  }


  void pop_back() {
    if (_M_finish._M_cur != _M_finish._M_first) {
      //最后缓冲区有一个元素
      --_M_finish._M_cur;//调整指针，相当于排除了最后元素
      destroy(_M_finish._M_cur);//将最后元素析构掉
    }
    else
      _M_pop_back_aux();
  }

  void pop_front() {
    if (_M_start._M_cur != _M_start._M_last - 1) {
      destroy(_M_start._M_cur);
      ++_M_start._M_cur;
    }
    else 
      _M_pop_front_aux();
  }