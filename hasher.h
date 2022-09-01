#pragma once

#include <vector>
#include <random>
#include <functional>

template<typename T>
std::size_t hash(const T & value){
	return std::hash<T>(value);
}

std::size_t randomNumber(std::size_t min, std::size_t max);
