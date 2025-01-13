#include "../src/orderbook/OrderBook.hpp"
#include <gtest/gtest.h>

class OrderBookTest : public testing::Test
{
protected:
  static std::map<std::string, int> symbol_to_index_map;

  static void SetUpTestSuite()
  {
    symbol_to_index_map = {{"AAPL", 1}, {"GOOG", 2}, {"NVDA", 3}};
  }
};
std::map<std::string, int> OrderBookTest::symbol_to_index_map;

TEST_F(OrderBookTest, OrderBook_Hash_Consistent_Test)
{
  for (auto it : OrderBookTest::symbol_to_index_map)
  {
    orderbook::Order ok{100, 900, it.second, orderbook::OrderType::BUY}; 
    auto hash = orderbook::OrderHash{}(orderbook::OrderKey(ok));
    EXPECT_EQ(
      (std::hash<long>{}(ok.instrument) ^ (std::hash<long>{}(ok.quantity) << 1) ^ 
      (std::hash<int>{}(static_cast<int>(ok.order_type)) << 2) ^ (std::hash<long>{}(ok.time_stamp) << 4)), 
      hash);
  }
}