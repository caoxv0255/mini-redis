#include"core/kv_store.h"
#include"core/list.h"
#include<iostream>
#include<stdexcept>
namespace mini_redis{
namespace core{

//类型检查辅助函数
bool KVStore::is_list_key(const std::string& key) const{
	return list_data_.find(key)!=list_data_.end();
}

bool KVStore::is_string_key(const std::string& key) const{
	return data_.find(key)!=data_.end();
}

//字符串操作
void KVStore::set(const std::string& key, const std::string& value){
	if(is_list_key(key)){
		throw std::runtime_error("Type mismatch: key'"+key+"'is a list");
	}
	data_[key]=value;
}

std::optional<std::string> KVStore::get(const std::string& key) const{
	if(is_list_key){
		throw std::runtime_error("Type mis match: key'"+key+"'is a list");
	}
	auto it = data_.find(key);
	if(it!=data_.end()){
		return it->second;
	}
	return std::nullopt;
}

//列表操作 - lpush
bool KVStore::lpush(const std::string& key, const std::string& value){
	if(is_string_key(key)){
		throw std::runtime_error("Type mismatch: key'"+key+"'is a string");
	}
	list_data_[key].push_front(value);
	return true;
}

//列表操作 - rpush
bool KVStore::rpush(const std::string& key, const std::string& value){
	if(is_string_key(key)){
		throw std::runtime_error("Type mismatch: key'"+key+"'is a string");
	}
	list_data_[key].push_back(value);
	return true;
}

//列表操作 - lpop
std::optional<std::string>KVStore::lpop(const std::string& key){
	if(is_string_key(key)){
		throw std::runtime_error("Type mismatch: key'"+key+"'is a string");
	}
	auto it = list_data_.find(key);
	if(it!=list_data_.end()){
		auto result = it->second.pop_front();
		if(it->second.empty()){
			list_data_.erase(it);
		}
		return result;
	}
	return std::nullopt;
}

//列表操作 - rpop
std::optional<std::string>KVStore::rpop(const std::string& key){
	if(is_string_key(key)){
		throw std::runtime_error("Type mismatch: key'"+key+"'is a string");
	}
	auto it = list_data_.find(key);
	if(it!=list_data_.end()){
		auto result = it->second.pop_back();
		if(it->second.empty()){
			list_data_.erase(it);
		}
		return result;
	}
	return std::nullopt;
}

//列表长度 - llen
size_t KVStore::llen(const std::string& key){
	if(is_string_key(key)){
		throw std::runtime_error("Type mismatch: key'"+key+"'is a string");
	}
	auto it = list_data_.find(key);
	if(it!=list_data_.end()){
		return it->second.size();
	}
	return 0;
}

//删除操作
bool KVStore::del(const std::string& key){
	bool erased_string = data_.erase(key)>0;
	bool erased_list = list_data_.erase(key)>0;
	return erased_string || erased_list;
}

//容器大小
size_t KVStore::size() const{
	return data_.size()+list_data_.size();
}

//清空操作
void KVStore::clear(){
	data_.clear();
	list_data_.clear();
}

//打印所有数据（调试用）
void KVStore::print_all() const{
	std::cout << "=== String Data ===" << std::endl;
    for (const auto& pair : data_) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "=== List Data ===" << std::endl;
    for (const auto& pair : list_data_) {
        std::cout << pair.first << ": ";
        pair.second.printList();
    }
}
} // namespace core
} // namespace mini_redis
