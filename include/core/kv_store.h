#ifndef MINI_REDIS_KV_STORE_H
#define MINI_REDIS_KV_STORE_H

#include<string>
#include<unordered_map>
#include<optional>

namespace mini-redis{
namespace core{
class KVStore{
	private:
		std::unordered_map<std::string, std::string> data;

public:
    // 核心操作
    void set(const std::string& key, const std::string& value);

    // 使用std::optional明确表达"key可能不存在"
    std::optional<std::string> get(const std::string& key) const;

    bool del(const std::string& key);
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }

    // 调试与监控
    void print_all() const;

    // 扩展预留
    void clear() { data_.clear(); }

private:
    // 内部辅助函数
    void log_operation(const std::string& op, const std::string& key) const;
};

} // namespace core
} // namespace mini_redis

#endif // MINI_REDIS_KV_STORE_H
