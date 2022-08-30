#pragma once

#include <vector>
#include "hash_container.h"

template<typename T>
class HashForLuxoft{
public:
	HashForLuxoft();

	bool add(T && value);
	void remove(const T & value);
	bool find(const T & value);
	void display();

private:
	HashContainer<HashContainer<T>> m_table;
};

