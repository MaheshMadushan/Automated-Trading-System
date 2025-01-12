cmake_minimum_required(VERSION 3.14)
project(mini-ats)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCES
    test/OrderBookTest.cpp)

add_executable(
        ats
        src/main.cpp
    )

# target_sources(mini-ats PUBLIC "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/main.cpp>")
enable_testing()

add_executable(
    OrderBookTest
    tests/OrderBookTest.cpp
)

target_link_libraries(
    OrderBookTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(OrderBookTest)