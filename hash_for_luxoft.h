#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "hash_container.h"

template<typename T>
class HashForLuxoft: protected HashContainer<std::unique_ptr<HashContainer<T>>>{
	using Base = HashContainer<std::unique_ptr<HashContainer<T>>>;
public:
	//HashForLuxoft();
	HashForLuxoft()
		: HashContainer<std::unique_ptr<HashContainer<T>>>(){
	}

	void add(T && value){
		if(Base::m_count == Base::m_values.size()){
			Base::resize(true);
		}
		auto & container = containerForValue(value);
		if(container.empty()){
			++Base::m_count;
		}
		container.add(hash(value), std::move(value));
	}

	void remove(const T & value){
		auto & container = containerForValue(value);
		container.remove(hash(value), value);
		if(container.empty()){
			--Base::m_count;
		}
		if(Base::m_count < Base::m_values.size() / 3){
			Base::resize(false);
		}
	}

	bool find(const T & value){
		return containerForValue(value).find(hash(value), value).has_value();
	}

	void display(){
		std::cout<<std::endl<<"Hash table:";
		for(auto & it: Base::m_values){
			for(auto & container: it){
				std::cout<<std::endl;
				container->display();
			}
		}
		std::cout<<std::endl<<"Hash table end.";
	}

private:
	HashContainer<T> & containerForValue(const T & value){
		std::size_t key = hash(value);
		std::size_t i = Base::index(key);
		auto & storage = Base::m_values[i];
		if(storage.empty()){
			storage.push_back(std::make_unique<HashContainer<T>>());
		}
		return *(storage.front());
	}
};
