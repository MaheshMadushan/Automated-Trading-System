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

TEST_F(OrderBookTest, OrderBook_Hash_Consistentency_Test)
{
  for (auto it : OrderBookTest::symbol_to_index_map)
  {
    orderbook::Order order{100, 900, 100, it.second, orderbook::OrderType::BUY};
    auto hash = orderbook::OrderHash{}(orderbook::OrderKey(order));
    EXPECT_EQ(
        (std::hash<long>{}(order.instrument) ^ (std::hash<long>{}(order.quantity) << 1) ^ (std::hash<long>{}(static_cast<int>(order.order_type)) << 2) ^ 
        (std::hash<long>{}(order.time_stamp) << 4) ^ (std::hash<long>{}(order.price) << 6)),
        hash);
  }
}