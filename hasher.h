#pragma once

#include <vector>
#include <random>
#include <functional>

template<typename T>
std::size_t hash(const T & value){
	return std::hash<T>(value);
}

std::size_t randomNumber(std::size_t min, std::size_t max){
	static std::random_device r;
	static std::mt19937_64 engine(r());
	std::uniform_int_distribution<long long> dist(min, max);
	return dist(engine);
}
