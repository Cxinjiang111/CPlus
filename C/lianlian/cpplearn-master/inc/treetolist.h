#ifndef __TREE_TO_ARRAY_H__
#define __TREE_TO_ARRAY_H__
#include <iostream>
using namespace std;
class Tree
{
public:
    Tree() : data(0), left(nullptr), right(nullptr) {}
    Tree(int dt) : data(dt), left(nullptr), right(nullptr) {}
    int data;
    Tree *left;
    Tree *right;
};

class Node
{
public:
    Node() : data(0), prev(nullptr), next(nullptr) {}
    Node(int dt) : data(dt), prev(nullptr), next(nullptr) {}
    int data;
    Node *prev;
    Node *next;
};

class List
{
public:
    List() : head(nullptr), tail(nullptr) {}
    ~List();
    Node *head;
    Node *tail;
};

void CreateList(Node *node, List *List);
void MidVisit(Tree *root, List *list);
extern void Test();
#endif