#include "hasher.h"

std::size_t randomNumber(std::size_t min, std::size_t max){
	static std::random_device r;
	static std::mt19937_64 engine(r());
	std::uniform_int_distribution<long long> dist(min, max);
	return dist(engine);
}
