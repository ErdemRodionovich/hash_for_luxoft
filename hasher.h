#pragma once

#include <vector>
#include <random>
#include <functional>
#include <type_traits>

template<typename T>
std::size_t hash(const T & value){
	if constexpr(std::is_same_v<T, int>){
		return std::hash<T>()(value);
	}
	else{
		return std::hash<T>(value);
	}
}

std::size_t randomNumber(std::size_t min, std::size_t max);
