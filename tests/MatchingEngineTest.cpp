#include "../src/matching/MatchingEngine.hpp"
#include "Setup.hpp"

TEST_F(BaseTest, Matching_Algorithm_Test)
{
  long instrumentIndex(1);
  MatchingEngine me{{instrumentIndex}};
  for (auto sell_order : BaseTest::sell_orders)
  {
    me.matchOrder(sell_order);
  }
  for (auto buy_order : BaseTest::buy_orders)
  {
    me.matchOrder(buy_order);
  }   

  auto sell_ordrs = me.getOrderBook(instrumentIndex)->getSellOrders();
  auto buy_ordrs = me.getOrderBook(instrumentIndex)->getBuyOrders();
  while (sell_ordrs.empty() != true)
  {
    orderbook::Order sell_ordr = sell_ordrs.top();
    sell_ordrs.pop();
  }

  while (buy_ordrs.empty() != true)
  {
    orderbook::Order buy_ordr = buy_ordrs.top();
    buy_ordrs.pop();
  }
}