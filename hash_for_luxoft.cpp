#include "hash_for_luxoft.h"
#include "hash_container.h"

template<typename T>
HashForLuxoft<T>::HashForLuxoft()
	: HashContainer<std::unique_ptr<HashContainer<T>>>(){
}

template<typename T>
void HashForLuxoft<T>::add(T &&value) {
	if(m_count == m_values.size()){
		resize(true);
	}
	auto & container = containerForValue(value);
	if(container.empty()){
		++m_count;
	}
	container.add(key, std::move(value));
}

template<typename T>
void HashForLuxoft<T>::remove(const T &value) {
	auto & container = containerForValue(value);
	container.remove(value);
	if(container.empty()){
		--m_count;
	}
	if(m_count < m_values.size() / 3){
		resize(false);
	}
}

template<typename T>
bool HashForLuxoft<T>::find(const T &value) {
	return containerForValue(value).find(value);
}

template<typename T>
void HashForLuxoft<T>::display() {

}

template<typename T>
HashContainer<T>& HashForLuxoft<T>::containerForValue(const T &value) {
	std::size_t key = hash(value);
	std::size_t i = index(key);
	auto & storage = m_values[i];
	if(storage.empty()){
		storage.push_back(HashContainer<T>());
	}
	return storage.front();
}
