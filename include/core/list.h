#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <optional>
#include <string>

// 前向声明节点结构
namespace core {
    template <typename T> struct ListNode;
}

namespace core {

template <typename T>
class List {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    std::size_t size_;

public:
    // 构造与析构
    List();
    ~List();
    
    // 拷贝控制
    List(const List& other);
    List& operator=(const List& other);
    
    // 移动控制
    List(List&& other) noexcept;
    List& operator=(List&& other) noexcept;

    // 元素访问与修改
    void push_front(const T& value);
    void push_back(const T& value);
    std::optional<T> pop_front();
    std::optional<T> pop_back();
    void clear();

    // 容量
    std::size_t size() const;
    bool empty() const;

    // 辅助函数 (仅用于测试展示)
    void printList() const;
};

// 为了编译通过，模板的实现通常需要在头文件可见，或者包含实现文件
// 这里我们采用包含 .tpp 的方式，或者直接在此处包含实现
// 为了符合你的要求（.cpp文件），在实际编译中，模板实现通常放在头文件末尾或单独的 .tpp 中
// 这里为了演示，我将声明留在这里，实现放在 src 中，但在实际 C++ 项目中，模板通常不分离编译
// 如果你必须分离，需要在 .cpp 中显式实例化所有类型（如 List<int>, List<string>），这限制了泛型

} // namespace core

#endif // LIST_H
