cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME hash_for_luxoft)

project("${TARGET_NAME}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TARGET_SOURCES
	hasher.cpp
	hasher.h
	hash_container.cpp
	hash_container.h
	hash_for_luxoft.cpp
	hash_for_luxoft.h
	main.cpp
)

add_executable("${TARGET_NAME}" "${TARGET_SOURCES}")
