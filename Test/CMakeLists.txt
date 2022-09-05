
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_TARGET_NAME test_hash_for_luxoft)

set(TEST_TARGET_SOURCES
	../hasher.cpp
	../hasher.h
	../hash_container.h
	../hash_for_luxoft.h
	test_hash.cpp
)

add_executable(
  ${TEST_TARGET_NAME}
  ${TEST_TARGET_SOURCES}
)
target_link_libraries(
  ${TEST_TARGET_NAME}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET_NAME})
