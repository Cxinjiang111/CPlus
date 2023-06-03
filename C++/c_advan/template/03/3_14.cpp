#include<iostream>
using namespace std;
struct Node {
    Node *next_, *prev_;

    Node() 
        : next_(this), prev_(this)
    {}

    ~Node() { 
        unlink();
    }

    void push_back(Node* n) {
        n->next_ = this;
        n->prev_ = prev_;
        prev_->next_ = n;
        prev_ = n;
    }

    void unlink() {
        Node *next = next_, *prev = prev_;
        next->prev_ = prev;
        prev->next_ = next;
        next_ = this;
        prev_ = this;
    }
};
template<class T>
struct Iterator
{
    typedef T                         value_type;
    typedef T                         difference_type;
    typedef T*                        pointer;
    typedef T&                        reference;

    T& operator*() const { return current->value; }
    bool operator!=(const Iterator& rhs) { return (*_current != rhs._current); }
    Iterator& operator++()
    {
        current = current->next;
        return *this;
    }
    
};
template <typename T>
class Linked_List
{
public:
    struct Iterator;
    struct Node;
public:
    Linked_List();
    ~Linked_List() noexcept(false);
    Linked_List(const Linked_List&) = delete;
    Linked_List(Linked_List&&) = delete;
    Linked_List& operator=(const Linked_List&) = delete;
    Linked_List& operator=(Linked_List&&) = delete;

    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    bool empty() const;
    T back() const;
    T front() const;
    //void swap(T, T);
    //void insert(Iterator, T);
    //void erase(Iterator);
    //Iterator begin() const;
    //Iterator end() const;
private:
    Node* head;
    Node* tail;
};

template<typename T>
struct Linked_List<T>::Node
{
    Node() : prev(nullptr), next(nullptr) {}
    Node(T t) : value(t), prev(nullptr), next(nullptr) {}
    Node* prev;
    Node* next;
    T value;
};