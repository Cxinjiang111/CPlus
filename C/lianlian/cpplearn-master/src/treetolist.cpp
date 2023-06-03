#include "../inc/treetolist.h"
#include <iostream>
using namespace std;

List::~List()
{
    while (head != nullptr && tail != nullptr)
    {
        cout << "head->data is " << head->data << endl;
        auto cur = head;
        head = head->next;
        delete (cur);
    }
}
void CreateList(Node *node, List *list)
{
    if (list->head == list->tail && list->tail == nullptr)
    {
        list->head = node;
        list->tail = node;
        return;
    }

    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
}

void MidVisit(Tree *root, List *list)
{
    if (root->left != nullptr)
    {
        MidVisit(root->left, list);
    }

    CreateList(new Node(root->data), list);

    if (root->right != nullptr)
    {
        MidVisit(root->right, list);
    }
}

void Test()
{
    //假定构造二叉树如下
    /*
         4
        / \
       2   5
      / \
     1   3
    */
    auto tr4 = new Tree(4);
    auto tr2 = new Tree(2);
    auto tr5 = new Tree(5);
    auto tr1 = new Tree(1);
    auto tr3 = new Tree(3);
    tr4->left = tr2;
    tr5->right = tr5;
    tr2->left = tr1;
    tr2->right = tr3;

    //测试生成List
    auto list = new List();
    MidVisit(tr4, list);
    //期待输出1234
    for (auto it = list->head; it != nullptr; it = it->next)
    {
        cout << it->data << endl;
    }

    delete (tr4);
    delete (tr2);
    delete (tr5);
    delete (tr1);
    delete (tr3);
    delete (list);
}