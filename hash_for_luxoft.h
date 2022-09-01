#pragma once

#include <vector>
#include <memory>
#include "hash_container.h"

template<typename T>
class HashForLuxoft: protected HashContainer<std::unique_ptr<HashContainer<T>>>{
	using Base = HashContainer<std::unique_ptr<HashContainer<T>>>;
public:
	HashForLuxoft();

	void add(T && value);
	void remove(const T & value);
	bool find(const T & value);
	void display();

private:
	HashContainer<T> & containerForValue(const T & value);
};
