#include "hash_container.h"

#include <algorithm>
#include <iostream>

template<typename T>
void HashContainer<T>::add(const std::size_t & key, T &&value) {
	if(m_count == m_values.size()){
		resize(true);
	}
	std::size_t i = index(key);
	std::list<T> & storage = m_values[i];
	if(storage.empty() || std::find(storage.begin(), storage.end(), value) == storage.end()){
		storage.push_back(std::move(value));
		++m_count;
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
			--m_count;
			if(m_count < m_values.size() / 3){
				resize(false);
			}
		}
	}
}

template<typename T>
std::optional<std::reference_wrapper<T>> HashContainer<T>::find(const std::size_t & key, const T &value) {
	std::size_t i = index(key);
	if(m_values.size() > i){
		std::list<T> & storage = m_values[i];
		if(auto it = std::find(storage.begin(), storage.end(), value); it != storage.end()){
			return std::optional<std::reference_wrapper<T>>(*it);
		}
	}
	return std::nullopt;
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
std::size_t HashContainer<T>::index(const std::size_t &key, std::size_t m) {
	if(m_values.empty()){
		return 0;
	}
	if(m == 0){
		m = m_values.size();
	}
	return ((m_a*key+m_b)%m_p)%m;
}

template<typename T>
void HashContainer<T>::resize(bool toUpper){
	std::size_t newSize = (toUpper) ? m_values.size() * 2 : m_values.size() / 2;
	if(newSize == 0 && toUpper){
		newSize = 1;
	}
	std::list<std::list<T>::iterator> forDelete;
	for(std::size_t i=0; i<m_values.size(); ++i){
		for(auto it = m_values[i].begin(); it != m_values[i].end(); ++it){
			std::size_t key = hash(*it);
			std::size_t newIndex = index(key, newSize);
			if(newIndex != i){
				m_values[newIndex].push_back(std::move(*it));
				forDelete.push_back(it);
			}
		}
		if(!forDelete.empty()){
			for(auto it = forDelete.rbegin(); it != forDelete.rend(); ++it){
				m_values[i].erase(*it);
			}
			forDelete.clear();
		}
	}
	m_values.resize(newSize);
}
