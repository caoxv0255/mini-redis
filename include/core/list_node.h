#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <cstddef>

namespace core {

template <typename T>
struct ListNode {
    T value;
    ListNode* prev;
    ListNode* next;

    // 构造函数
    ListNode(const T& val = T(), ListNode* p = nullptr, ListNode* n = nullptr)
        : value(val), prev(p), next(n) {}
};

} // namespace core

#endif // LIST_NODE_H
