#include "hash_container.h"

#include <algorithm>
#include <iostream>

template<typename T>
bool HashContainer<T>::add(const std::size_t & key, T &&value) {
	std::size_t i = index(key);
	if(m_values.size() <= i){
		m_values.resize(i+1);
	}
	std::list<T> & storage = m_values[i];
	if(storage.empty() || std::find(storage.begin(), storage.end(), value) == storage.end()){
		storage.push_back(std::move(value));
	}
}

template<typename T>
void HashContainer<T>::remove(const std::size_t & key, const T &value) {
	std::size_t i = index(key);
	if(m_values.size() > i){
		std::list<T> & storage = m_values[i];
		auto it = std::find(storage.begin(), storage.end(), value);
		if(it != storage.end()){
			storage.erase(it);
		}
	}
}

template<typename T>
bool HashContainer<T>::find(const std::size_t & key, const T &value) {
	std::size_t i = index(key);
	if(m_values.size() > i){
		std::list<T> & storage = m_values[i];
		return std::find(storage.begin(), storage.end(), value) != storage.end();
	}
	return false;
}

template<typename T>
void HashContainer<T>::display() {
	for(auto & it: m_values){
		for(auto & v: it){
			std::cout<<v<<", ";
		}
	}
}

template<typename T>
std::size_t HashContainer<T>::index(const std::size_t &key) {
	if(m_m == 0){
		return 0;
	}
	return ((m_a*key+m_b)%m_p)%m_m;
}
