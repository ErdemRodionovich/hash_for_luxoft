#include "hash_for_luxoft.h"
#include "hash_container.h"
#include <iostream>

template<typename T>
HashForLuxoft<T>::HashForLuxoft()
	: HashContainer<std::unique_ptr<HashContainer<T>>>(){
}

template<typename T>
void HashForLuxoft<T>::add(T &&value) {
	if(Base::m_count == Base::m_values.size()){
		Base::resize(true);
	}
	auto & container = containerForValue(value);
	if(container.empty()){
		++Base::m_count;
	}
	container.add(hash(value), std::move(value));
}

template<typename T>
void HashForLuxoft<T>::remove(const T &value) {
	auto & container = containerForValue(value);
	container.remove(value);
	if(container.empty()){
		--Base::m_count;
	}
	if(Base::m_count < Base::m_values.size() / 3){
		Base::resize(false);
	}
}

template<typename T>
bool HashForLuxoft<T>::find(const T &value) {
	return containerForValue(value).find(value);
}

template<typename T>
void HashForLuxoft<T>::display() {
	for(auto & it: Base::m_values){
		for(auto & container: it){
			std::cout<<std::endl;
			container.display();
		}
	}
}

template<typename T>
HashContainer<T>& HashForLuxoft<T>::containerForValue(const T &value) {
	std::size_t key = hash(value);
	std::size_t i = Base::index(key);
	auto & storage = Base::m_values[i];
	if(storage.empty()){
		storage.push_back(HashContainer<T>());
	}
	return storage.front();
}
