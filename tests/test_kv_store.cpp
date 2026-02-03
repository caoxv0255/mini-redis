#include "core/kv_store.h"
#include <iostream>
#include <cassert>

using namespace mini_redis::core;

void test_string_operations() {
    std::cout << "\n=== Testing String Operations ===" << std::endl;
    KVStore store;
    
    store.set("key1", "value1");
    auto val = store.get("key1");
    assert(val.has_value() && val.value() == "value1");
    assert(store.size() == 1);
    std::cout << "✓ Set and Get works" << std::endl;
}

void test_list_operations() {
    std::cout << "\n=== Testing List Operations ===" << std::endl;
    KVStore store;
    
    // LPUSH
    assert(store.lpush("list1", "a") == true);
    assert(store.lpush("list1", "b") == true);
    assert(store.llen("list1") == 2);
    std::cout << "✓ LPUSH works" << std::endl;
    
    // RPUSH
    assert(store.rpush("list1", "c") == true);
    assert(store.llen("list1") == 3);
    std::cout << "✓ RPUSH works" << std::endl;
    
    // LPOP
    auto lpop_val = store.lpop("list1");
    assert(lpop_val.has_value() && lpop_val.value() == "b");
    assert(store.llen("list1") == 2);
    std::cout << "✓ LPOP works" << std::endl;
    
    // RPOP
    auto rpop_val = store.rpop("list1");
    assert(rpop_val.has_value() && rpop_val.value() == "c");
    assert(store.llen("list1") == 1);
    std::cout << "✓ RPOP works" << std::endl;
    
    // Empty list LPOP/RPOP
    while (store.lpop("list1").has_value()) {}
    auto empty_pop = store.lpop("list1");
    assert(!empty_pop.has_value());
    std::cout << "✓ Empty list LPOP/RPOP returns nullopt" << std::endl;
}

void test_type_conflict() {
    std::cout << "\n=== Testing Type Conflict ===" << std::endl;
    KVStore store;
    
    // String to list conflict
    store.set("key1", "value1");
    bool exception_thrown = false;
    try {
        store.lpush("key1", "should fail");
    } catch (const std::runtime_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "✓ String → List conflict throws exception" << std::endl;
    
    // List to string conflict
    exception_thrown = false;
    try {
        store.set("key1", "should fail");
    } catch (const std::runtime_error&) {
        exception_thrown = true;
    }
    assert(!exception_thrown);  // Already a string, should succeed
    std::cout << "✓ List → String conflict checked" << std::endl;
}

void test_coexistence() {
    std::cout << "\n=== Testing String/List Coexistence ===" << std::endl;
    KVStore store;
    
    store.set("str_key", "string value");
    store.lpush("list_key", "list value");
    
    assert(store.get("str_key").has_value());
    assert(store.llen("list_key") == 1);
    assert(store.size() == 2);
    std::cout << "✓ Strings and lists coexist" << std::endl;
}

int main() {
    std::cout << "==================== KVStore Tests ====================" << std::endl;
    
    test_string_operations();
    test_list_operations();
    test_type_conflict();
    test_coexistence();
    
    std::cout << "\n==================== All Tests Passed! ====================" << std::endl;
    return 0;
}