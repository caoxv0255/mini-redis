#ifndef MINI_REDIS_KV_STORE_H
#define MINI_REDIS_KV_STORE_H

#include<string>
#include<unordered_map>
#include<optional>
#include "core/list.h"

namespace mini_redis{
namespace core{
class KVStore{
	private:
        bool is_string_key(const std::string& key) const;
        bool is_list_key(const std::string& key) const;
		std::unordered_map<std::string, std::string> data_;
		std::unordered_map<std::string, List<std::string>> list_data_;

public:
    // 核心操作
    void set(const std::string& key, const std::string& value);

    // 使用std::optional明确表达"key可能不存在"
    std::optional<std::string> get(const std::string& key) const;
    bool del(const std::string& key);
    size_t size() const;
    bool empty() const;

    // 调试与监控
    void print_all() const;

    // 扩展预留
    void clear() { data_.clear(); }
    //新增列表操作方法
    bool lpush(const std::string& key, const std::string& value);
    bool rpush(const std::string& key, const std::string& value);
    std::optional<std::string> lpop(const std::string& key);
    std::optional<std::string> rpop(const std::string& key);
    size_t llen(const std::string& key);

private:
    // 内部辅助函数
};

} // namespace core
} // namespace mini_redis

#endif // MINI_REDIS_KV_STORE_H
