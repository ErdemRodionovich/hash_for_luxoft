#pragma once

#include <vector>
#include <list>
#include <limits>
#include <optional>
#include <functional>
#include <algorithm>
#include <iostream>
#include <exception>
#include <memory>

#include "hasher.h"

template<typename T>
class HashContainer{
public:
	HashContainer()
		: m_p(std::numeric_limits<std::size_t>::max())
		, m_values()
	{
		m_a = randomNumber(1, m_p-1);
		m_b = randomNumber(0, m_p-1);
		static std::size_t lastID = 0;
		m_id = ++lastID;
	}

	void add(const std::size_t & key, T && value){
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

	void remove(const std::size_t & key, const T & value){
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

	std::optional<std::reference_wrapper<T>> find(const std::size_t & key, const T & value){
		std::size_t i = index(key);
		if(m_values.size() > i){
			std::list<T> & storage = m_values[i];
			if(auto it = std::find(storage.begin(), storage.end(), value); it != storage.end()){
				return std::optional<std::reference_wrapper<T>>(*it);
			}
		}
		return std::nullopt;
	}

	void display(){
		for(auto & it: m_values){
			for(auto & v: it){
				std::cout<<v<<", ";
			}
		}
	}

	std::size_t id(){
		return m_id;
	}

	bool empty(){
		return m_count == 0;
	}

	bool operator ==(const HashContainer<T> & other){
		return this == &other;
	}

protected:
	std::size_t m_count = 0;
	std::vector<std::list<T>> m_values;

	std::size_t index(const std::size_t & key, std::size_t m = 0){
		if(m_values.empty()){
			return 0;
		}
		if(m == 0){
			m = m_values.size();
		}
		return ((m_a*key+m_b)%m_p)%m;
	}

	void resize(bool toUpper){
		std::size_t newSize = (toUpper) ? m_values.size() * 2 : m_values.size() / 2;
		if(newSize == 0 && toUpper){
			newSize = 1;
		}
		if(toUpper){
			m_values.resize(newSize);
		}
		std::list<typename std::list<T>::iterator> forDelete;
		for(std::size_t i=0; i<m_values.size(); ++i){
			for(auto it = m_values[i].begin(); it != m_values[i].end(); ++it){
				std::size_t key = hash(*it);
				std::size_t newIndex = index(key, newSize);
				if(newIndex != i){
					if(newIndex < 0 || newIndex >= m_values.size()){
						throw std::runtime_error("Index out of range!");
					}
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
		if(!toUpper){
			m_values.resize(newSize);
		}
	}

private:
	std::size_t m_p = 0;
	std::size_t m_a = 0;
	std::size_t m_b = 0;
	std::size_t m_id = 0;
};

template<typename T>
std::size_t hash(const HashContainer<T> & container){
	return container.id();
}

template<typename T>
std::size_t hash(const std::unique_ptr<HashContainer<T>> & container){
	return container->id();
}
