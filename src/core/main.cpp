#include "core/kv_store.h"
#include <iostream>

int main() {
    using namespace mini_redis::core;
    
    KVStore store;
    
    // 测试字符串操作
    std::cout << "=== String Operations ===" << std::endl;
    store.set("name", "mini-redis");
    store.set("version", "1.0");
    
    auto name = store.get("name");
    if (name.has_value()) {
        std::cout << "name: " << name.value() << std::endl;
    }
    
    // 测试列表操作
    std::cout << "\n=== List Operations ===" << std::endl;
    store.lpush("mylist", "world");
    store.lpush("mylist", "hello");
    store.rpush("mylist", "!");
    
    std::cout << "List length: " << store.llen("mylist") << std::endl;
    
    auto elem = store.lpop("mylist");
    if (elem.has_value()) {
        std::cout << "Lopped from front: " << elem.value() << std::endl;
    }
    std::cout << "List length after lpop: " << store.llen("mylist") << std::endl;
    
    // 测试类型冲突
    std::cout << "\n=== Type Conflict Test ===" << std::endl;
    try {
        store.set("mylist", "should fail");
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    store.print_all();
    return 0;
}
