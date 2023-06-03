#include<iostream>
#include<vector>
using namespace std;
//单项链表
struct int_node{
    int val;
    int_node*next;
};
template<class Node>
struct node_warp{
    Node*ptr;
    node_warp(Node *head=0):ptr(head){}
    ~node_warp(){}
    node_warp operator++(){
        ptr=ptr->next; 
        return ptr;   
    } 
    node_warp operator+(int){
        node_warp tmp=*this;
        ++*this; 
        return tmp;   
    }     
    Node& operator*(){
        return *ptr
    }  
    Node* operator->(){
        return ptr
    }
    bool operator==(const node_warp&s)
    {
        if(s.ptr==ptr)
            return true;
    }
    bool operator!=(const node_warp&s)
    {
        return !(this==s);
    }
};
template<typename Inputiterator,typename T>
Inputiterator *find2(Inputiterator *first,Inputiterator *end,T c)
{
    while (*first!=c&&first!=end)
    {
        ++first;
    }
    return first==end?end:first;
}
void t1()
{
    int val=0;
    node_warp<int_node> *list_head;
    node_warp<int_node> *list_end;
    find2(list_head,list_end,val);//共享该函数 find是一个一般化函数

}