#include "OrderBook.hpp"

using namespace orderbook;

void OrderBook::addOrder(const orderbook::Order &order_to_add)
{
    const OrderKey orderKey(order_to_add);
    m_all_orders.emplace(std::make_pair(orderKey, order_to_add));

    if (Order::OrderType::BUY == order_to_add.order_type)
    {
        m_buy_orders_priority_q.emplace(order_to_add);
    }
    else if (Order::OrderType::SELL == order_to_add.order_type)
    {
        m_sell_orders_priority_q.emplace(order_to_add);
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
