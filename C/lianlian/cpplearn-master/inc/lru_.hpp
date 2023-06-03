#ifndef __LRU__H_
#define __LRU__H_
#include <string>
#include <iostream>
using namespace std;
class NodeLRU
{
public:
    NodeLRU(int v) : val(v), prev(nullptr), next(nullptr) {}

    int val;
    NodeLRU *prev;
    NodeLRU *next;
};
class LRU
{
public:
    LRU(int sz) : max_size(sz), cur_size(0), head(nullptr), tail(nullptr) {}
    LRU() = default;
    void insert(int val)
    {
        if (max_size == 0)
        {
            return;
        }

        if (head == tail && head == nullptr)
        {
            auto node = new NodeLRU(val);
            head = node;
            tail = node;
            cur_size++;
            return;
        }

        auto node_find = find(val);
        if (node_find == nullptr)
        {
            //节点数量达到上限
            if (cur_size >= max_size)
            {
                //删除尾节点
                auto deltail = tail;
                if (tail->prev != nullptr)
                {
                    tail->prev->next = nullptr;
                }

                tail = tail->prev;
                delete (deltail);
                cur_size--;
            }

            //插入头部节点
            auto node = new NodeLRU(val);
            node->next = head;
            head->prev = node;
            head = node;
            cur_size++;
            return;
        }

        //头部节点就不处理
        if (node_find == head)
        {
            return;
        }

        //如果是尾部节点
        if (node_find == tail)
        {
            node_find->prev->next = nullptr;
            tail = node_find->prev;
        }
        else
        {
            //先将node_find节点前后节点连接起来
            node_find->prev->next = node_find->next;
            node_find->next->prev = node_find->prev;
        }

        //在将node_find节点插入头部
        node_find->prev = nullptr;
        node_find->next = head;
        head = node_find;
    }

    NodeLRU *find(int sz)
    {
        auto node = head;
        while (node != nullptr)
        {
            if (node->val == sz)
            {
                return node;
            }
            node = node->next;
        }

        return nullptr;
    }

    void print()
    {
        for (auto node = head; node != nullptr; node = node->next)
        {
            cout << node->val << " -> ";
        }

        cout << "null" << endl;
    }

    ~LRU()
    {
        for (auto node = head; node != nullptr;)
        {
            auto nodedel = node;
            node = node->next;
            delete (nodedel);
        }
        head = nullptr;
        tail = nullptr;
    }

private:
    NodeLRU *head;
    NodeLRU *tail;
    int max_size;
    int cur_size;
};
#endif