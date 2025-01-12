#include "../src/orderbook/OrderBook.hpp"
#include <gtest/gtest.h>


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  std::cout << orderbook::OrderHash{}(orderbook::OrderKey(orderbook::Order{8,8,"A",orderbook::OrderType::BUY}));
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}