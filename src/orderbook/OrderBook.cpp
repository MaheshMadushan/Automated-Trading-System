#include "OrderBook.hpp"

using namespace orderbook;

inline void OrderBook::addOrder(const Order &order)
{
    const OrderKey orderKey(order);
    m_all_orders.emplace(std::make_pair(orderKey, order));

    if (Order::OrderType::BUY == order.order_type)
    {
        m_buy_orders_priority_q.emplace(order);
    }
    else if (Order::OrderType::SELL == order.order_type)
    {
        m_sell_orders_priority_q.emplace(order);
    }
    else
    {
        // unhandled order type
    }
}

void OrderBook::removeOrder(const Order &order_to_remove)
{
}

OrderBook::SellOrderPriorityQueue OrderBook::getSellOrders() const
{
    return m_sell_orders_priority_q;
}

OrderBook::BuyOrderPriorityQueue OrderBook::getBuyOrders() const
{
    return m_buy_orders_priority_q;
}
