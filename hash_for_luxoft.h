#pragma once

#include <vector>

template<typename T>
class HashForLuxoft{
public:
	HashForLuxoft();

	bool add(T && value);
	void remove(const T & value);
	bool find(const T & value);
	void display();

private:
	std::size_t m_p = 0;
	std::size_t m_a = 0;
	std::size_t m_b = 0;

};

