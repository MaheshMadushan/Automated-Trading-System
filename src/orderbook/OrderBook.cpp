#include "OrderBook.hpp"

inline void orderbook::OrderBook::addOrder(const Order& order)
{
    const orderbook::OrderKey orderKey(order);
    orders.emplace(std::make_pair(orderKey, order));
}

void orderbook::OrderBook::removeOrder(const Order& order_to_remove)
{
}


