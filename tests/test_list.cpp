#include "core/list.h"
#include <iostream>

using namespace std;
using namespace core;

int main() {
    cout << "==================== 链表测试开始 ====================" << endl;

    // 测试1: 基本功能 - push_back和push_front
    cout << "\n【测试1】基本功能测试 - push_back和push_front" << endl;
    List<string> list1;
    cout << "创建空列表，size: " << list1.size() << ", empty: " << boolalpha << list1.empty() << endl;
    
    list1.push_back("A");
    list1.push_back("B");
    list1.push_back("C");
    cout << "push_back A, B, C 后的列表: ";
    list1.printList();
    cout << "size: " << list1.size() << ", empty: " << boolalpha << list1.empty() << endl;
    
    list1.push_front("X");
    list1.push_front("Y");
    cout << "push_front X, Y 后的列表: ";
    list1.printList();
    cout << "size: " << list1.size() << endl;

    // 测试2: pop_front和pop_back
    cout << "\n【测试2】pop_front和pop_back测试" << endl;
    auto front_val = list1.pop_front();
    if (front_val.has_value()) {
        cout << "pop_front 返回值: " << front_val.value() << endl;
    } else {
        cout << "pop_front 失败: 列表为空" << endl;
    }
    cout << "当前列表: ";
    list1.printList();
    
    auto back_val = list1.pop_back();
    if (back_val.has_value()) {
        cout << "pop_back 返回值: " << back_val.value() << endl;
    } else {
        cout << "pop_back 失败: 列表为空" << endl;
    }
    cout << "当前列表: ";
    list1.printList();

    // 测试3: 边界条件 - 空列表操作
    cout << "\n【测试3】边界条件测试 - 空列表操作" << endl;
    List<string> empty_list;
    cout << "空列表 size: " << empty_list.size() << ", empty: " << boolalpha << empty_list.empty() << endl;
    
    auto empty_pop_front = empty_list.pop_front();
    if (!empty_pop_front.has_value()) {
        cout << "pop_front 空列表返回: nullopt (正确)" << endl;
    }
    
    auto empty_pop_back = empty_list.pop_back();
    if (!empty_pop_back.has_value()) {
        cout << "pop_back 空列表返回: nullopt (正确)" << endl;
    }

    // 测试4: 拷贝构造函数
    cout << "\n【测试4】拷贝构造函数测试" << endl;
    List<string> list2;
    list2.push_back("1");
    list2.push_back("2");
    list2.push_back("3");
    cout << "原列表list2: ";
    list2.printList();
    
    List<string> list3(list2);
    cout << "拷贝构造的list3: ";
    list3.printList();
    cout << "list2 size: " << list2.size() << ", list3 size: " << list3.size() << endl;

    // 测试5: 拷贝赋值运算符
    cout << "\n【测试5】拷贝赋值运算符测试" << endl;
    List<string> list4;
    list4 = list2;
    cout << "赋值后的list4: ";
    list4.printList();
    cout << "list2 size: " << list2.size() << ", list4 size: " << list4.size() << endl;

    // 测试6: 移动构造函数
    cout << "\n【测试6】移动构造函数测试" << endl;
    List<string> list5(std::move(list2));
    cout << "移动构造后的list5: ";
    list5.printList();
    cout << "list5 size: " << list5.size() << endl;
    cout << "原list2是否为空: " << boolalpha << (list2.size() == 0) << endl;

    // 测试7: 移动赋值运算符
    cout << "\n【测试7】移动赋值运算符测试" << endl;
    List<string> list6;
    list6 = std::move(list5);
    cout << "移动赋值后的list6: ";
    list6.printList();
    cout << "list6 size: " << list6.size() << endl;
    cout << "原list5是否为空: " << boolalpha << (list5.size() == 0) << endl;

    // 测试8: clear函数
    cout << "\n【测试8】clear函数测试" << endl;
    List<string> list7;
    list7.push_back("a");
    list7.push_back("b");
    list7.push_back("c");
    cout << "清空前list7: ";
    list7.printList();
    cout << "size: " << list7.size() << endl;
    
    list7.clear();
    cout << "清空后list7: ";
    list7.printList();
    cout << "size: " << list7.size() << ", empty: " << boolalpha << list7.empty() << endl;

    // 测试9: 频繁添加删除
    cout << "\n【测试9】频繁操作测试" << endl;
    List<int> list8;
    cout << "添加1-5:" << endl;
    for (int i = 1; i <= 5; i++) {
        list8.push_back(i);
        cout << " 添加 " << i << ", size: " << list8.size() << endl;
    }
    cout << "最终列表: ";
    list8.printList();
    
    cout << "删除元素:" << endl;
    while (!list8.empty()) {
        auto val = list8.pop_back();
        cout << " 删除 " << val.value() << ", size: " << list8.size() << endl;
    }

    // 测试10: 字符串测试
    cout << "\n【测试10】字符串类型测试" << endl;
    List<string> str_list;
    str_list.push_back("Hello");
    str_list.push_back("World");
    str_list.push_front("Coze");
    str_list.push_back("AI");
    cout << "字符串列表: ";
    str_list.printList();

    cout << "\n==================== 测试完成 ====================" << endl;
    return 0;
}
