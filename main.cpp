#include <iostream>
#include "hash_for_luxoft.h"

template<typename T>
using SomeHash = HashForLuxoft<T>;

int main(int argc, char **argv) {
	std::cout<<"Hash for Luxoft by Erdem Badluev:"<<std::endl;
	SomeHash<int> h;
	h.add(0);    //
	h.add(1);    //
	h.add(2);    //
	h.add(3);    //
	h.remove(0);  // required interfaces
	h.find(1);   //
	h.display();  // shows all values in hash with their positions
	return 0;
}
