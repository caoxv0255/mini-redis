#include<unorderd_map>
#include<string>

class KVStore{
	private:
		std::unordered_map<std::string,std::string> data;
	public:
		void set(const std::string& key,const std::string& value){
			data[key]=value;
		}
		std::string get(const std::string& key){
			auto it = data.find(key);
			if(it != data.end()){
				return it->second;
			}
			return "";
		}
		size_t size() const{
			return data.size();
		}

};
