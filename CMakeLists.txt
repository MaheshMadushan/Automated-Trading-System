cmake_minimum_required(VERSION 3.14)
project(mini-ats)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCES
    test/OrderBookTest.cpp)

add_executable(
        ats
        src/main.cpp
    )

enable_testing()

add_executable(
    run_tests
    src/matching/MatchingEngine.hpp
    src/matching/MatchingEngine.cpp
    src/orderbook/OrderBook.cpp
    src/orderbook/OrderBook.hpp
    tests/OrderBookTest.cpp
    tests/MatchingEngineTest.cpp
    tests/Setup.hpp
)

target_link_libraries(
  run_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)