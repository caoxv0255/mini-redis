#include "core/list.h"
#include "core/list_node.h"
#include <iostream>
#include <stdexcept>

// 为了使用 optional
#include <optional>

namespace core {

// --- 私有辅助结构或通用逻辑（如果需要） ---

// --- List 模板类实现 ---

template <typename T>
List<T>::List() : size_(0) {
    head = new ListNode<T>();
    tail = new ListNode<T>();
    head->next = tail;
    tail->prev = head;
}

template <typename T>
List<T>::~List() {
    clear();
    delete head;
    delete tail;
}

template <typename T>
List<T>::List(const List& other) : List() {
    for (ListNode<T>* cur = other.head->next; cur != other.tail; cur = cur->next) {
        push_back(cur->value);
    }
}

template <typename T>
typename List<T>::List& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        for (ListNode<T>* cur = other.head->next; cur != other.tail; cur = cur->next) {
            push_back(cur->value);
        }
    }
    return *this;
}

template <typename T>
List<T>::List(List&& other) noexcept 
    : head(other.head), tail(other.tail), size_(other.size_) {
    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
}

template <typename T>
typename List<T>::List& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        // 修正：原代码缺少 clear 和 delete，可能导致内存泄漏
        clear(); 
        delete head;
        delete tail;
        
        head = other.head;
        tail = other.tail;
        size_ = other.size_;
        
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
void List<T>::push_front(const T& value) {
    ListNode<T>* node = new ListNode<T>(value, head, head->next);
    head->next->prev = node;
    head->next = node;
    size_++;
}

template <typename T>
void List<T>::push_back(const T& value) {
    ListNode<T>* node = new ListNode<T>(value, tail->prev, tail);
    tail->prev->next = node;
    tail->prev = node;
    size_++;
}

template <typename T>
std::optional<T> List<T>::pop_front() {
    if (empty()) {
        return std::nullopt;
    }
    ListNode<T>* node = head->next;
    T val = node->value;
    head->next = node->next;
    node->next->prev = head;
    delete node;
    size_--;
    return val;
}

template <typename T>
std::optional<T> List<T>::pop_back() {
    if (empty()) {
        return std::nullopt;
    }
    ListNode<T>* node = tail->prev;
    T val = node->value;
    tail->prev = node->prev;
    node->prev->next = tail;
    delete node;
    size_--;
    return val;
}

template <typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
std::size_t List<T>::size() const {
    return size_;
}

template <typename T>
bool List<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void List<T>::printList() const {
    std::cout << "[";
    for (ListNode<T>* cur = head->next; cur != tail; cur = cur->next) {
        std::cout << cur->value;
        if (cur->next != tail) std::cout << " -> ";
    }
    std::cout << "]" << std::endl;
}

// --- 显式实例化 (关键) ---
// 为了让链接器能找到 List<string> 和 List<int> 的实现，
// 我们在这里显式实例化测试中用到的类型。
// 这是将模板分离到 .cpp 文件时必须做的步骤。
template class List<std::string>;
template class List<int>;

} // namespace core
