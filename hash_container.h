#pragma once

#include <vector>
#include <list>

template<typename T>
class HashContainer{
public:
	HashContainer(std::size_t p)
		: m_p(p)
	{
	}

	bool add(const std::size_t & key, T && value);
	void remove(const std::size_t & key, const T & value);
	bool find(const std::size_t & key, const T & value);
	void display();

private:
	std::size_t m_p = 0;
	std::size_t m_m = 0;
	std::size_t m_a = 0;
	std::size_t m_b = 0;

	std::vector<std::list<T>> m_values;

	std::size_t index(const std::size_t & key);
};
