#include<iostream>
//链表结点结构体
template<typename T>
class ListItem{
public:
    T getvalue(){return m_value;}
    ListItem(T _value):m_value(_value){}
    ListItem*getnext()const{return m_nextl}
private:
    T m_value;
    ListItem* m_next;
};
//操作链表的功能结构体
template<typename T>
class List{
public:
    void insert_front(T value){
        ListItem<T>* new_value=new ListItem<T>(value);
        new_value->m_next=m_first;
        m_first=new_value;
    }
    void insert_end(T value){
        ListItem<T>* new_value=new ListItem<T>(value);
        m_end->m_next=new_value;
        m_end=new_value;
    }
    void display(std::ostream&os=std::cout)const{
        ListItem<T>::it=m_first;
        while(it!=m_end){
            os<<*it<<"/t";
        }
        return os;
    }

private:
    ListItem<T>*m_first;
    ListItem<T>*m_end;
    long m_size;//含结点的个数
};
//链表的迭代器
template<class Item>
struct ListIter{
    Item*ptr;
    Item& operator++(){
        return ptr=ptr->getnext();
    }
};
//每种STL有自己的专属迭代器
