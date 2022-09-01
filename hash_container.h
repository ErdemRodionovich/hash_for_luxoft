#pragma once

#include <vector>
#include <list>
#include <limits>
#include <optional>
#include <functional>

#include "hasher.h"

template<typename T>
class HashContainer{
public:
	HashContainer()
		: m_p(std::numeric_limits<std::size_t>::max())
	{
		m_a = randomNumber(1, m_p-1);
		m_b = randomNumber(0, m_p-1);
		static std::size_t lastID = 0;
		m_id = ++lastID;
	}

	void add(const std::size_t & key, T && value);
	void remove(const std::size_t & key, const T & value);
	std::optional<std::reference_wrapper<T>> find(const std::size_t & key, const T & value);
	void display();

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

	std::size_t index(const std::size_t & key, std::size_t m = 0);
	void resize(bool toUpper);

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
