#include<vector>
#include<iostream>
#include<assert.h>
using namespace std;
template<typename T>
class Matrix {
public:
    vector<vector<T>> data;
    Matrix(const vector<vector<T>>& d)
        : data(d) {}
    std::pair<size_t, size_t> size() const {
        std::pair<size_t, size_t> s;
        s.first = data.size();
        s.second = data[0].size();
        return s;
    }
};
template<typename T>
class iterator
    {
        public:
            typedef iterator                    self_type;
            typedef T                           value_type;
            typedef T&                          reference;
            typedef T*                          pointer;
            typedef std::forward_iterator_tag   iterator_category;
            typedef int                         difference_type;

            iterator(pointer ptr) : ptr_(ptr) { }
            self_type operator++() { self_type i = *this; ptr_++; return i; }
            self_type operator++(int junk) { ptr_++; return *this; }
            reference operator*() { return *ptr_; }
            pointer operator->() { return ptr_; }
            bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
            bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        private:
            pointer ptr_;
            Matrix data_;
public:
    iterator begin()
    {
        return iterator(data_);
    }
    iterator end()
    {
        return iterator(data_ + size_);
    }
};
