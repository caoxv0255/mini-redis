#include "core/kv_store.h"
#include<iostream>
int main(){
	KVStore store;
	store.set("name","mini-redis");
	std::cout<<store.get("name")<<std::endl;
	return 0;
}
