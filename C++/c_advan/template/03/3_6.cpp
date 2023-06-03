#include<iterator>
using namespace std;
//定义新组件
template<class Node,class Reference,class Pointer>
struct node_wrap_base:public iterator<forward_iterator_tag,Node,ptrdiff_t,Pointer,Reference>//含有的5中类型
{
    typedef node_wrap_base<Node,Node&,Node*>                iterator;
    typedef node_wrap_base<Node,const Node&,const Node*>    const_iterator;
    Pointer                                                 ptr;
    node_wrap_base(Pointer p=0):ptr(p){}
    node_wrap_base(const iterator& x):ptr(x){}
    Reference operator*()const{return *ptr;}
    Pointer   operator->()const{return ptr;}
    void incr(){ptr=ptr->next;}
    bool operator==(const node_wrap_base&x)const{return ptr==x.ptr;}
    bool operator!=(const node_wrap_base&x)const{return ptr!=x.ptr;}
};
//
template<class Node>
struct node_warp:public node_wrap_base<Node,Node&,Node*>
{
    typedef node_wrap_base<Node,Node&,Node*> Base;
    node_warp(Node*p=0):Base(p){}
    node_warp(const node_warp<Node>&x):Base(x){}
    node_warp&operator++(){
        incr();
        return *this;
    }
    node_warp operator++(int){
        node_warp tmp=*this;
        incr();
        return tmp;
    }
};
template<class Node>
struct const_node_wrap:public node_warp_base<Node,const Node&,const Node*>
{
   typedef node_wrap_base<Node,const Node&,const Node*> Base;
   const_node_wrap(const Node*p=0):Base(p){}
   const_node_wrap(const node_warp<Node>&x):Base(x){}
   const_node_wrap&operator++(){ //a++
       incr();return *this;
   }
   const_node_wrap operator++(int){ //++a 
       const_node_wrap tmp=*this;
       incr();
       return tmp;
   }
};
//这个怎么用const 与非const 呢
