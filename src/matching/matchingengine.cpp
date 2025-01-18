#include "matchingengine.hpp"

void MatchingEngine::matchOrder(orderbook::Order &order)
{
    auto it = instrument_to_order_books_map.find(order.instrument);
    if (it == instrument_to_order_books_map.end())
    {
        // error return
    }

    const auto orderbook = it->second;
    if (orderbook == nullptr)
    {
        // error return
    }

    if (orderbook::Order::OrderType::SELL == order.order_type)
    {
        auto outstanding_buy_order = orderbook->getBuyOrders().top();
        while (orderbook->getBuyOrders().empty() != true)
        {
            orderbook->getBuyOrders().pop();
            if (outstanding_buy_order.price >= order.price)
            {
                if (outstanding_buy_order.quantity >= order.quantity)
                {
                    outstanding_buy_order.quantity -= order.quantity;
                    if (outstanding_buy_order.quantity > 0)
                    {
                        orderbook->addOrder(outstanding_buy_order);
                    }
                    return;
                }
                order.quantity -= outstanding_buy_order.quantity;
                outstanding_buy_order.quantity = 0;
                outstanding_buy_order = orderbook->getBuyOrders().top();
            }
            else
            {
                orderbook->addOrder(order);
                return;
            }
        }
    }
    else if (orderbook::Order::OrderType::BUY == order.order_type)
    {
        auto outstanding_sell_order = orderbook->getSellOrders().top();
        while (orderbook->getSellOrders().empty() != true)
        {
            orderbook->getSellOrders().pop();
            if (outstanding_sell_order.price <= order.price)
            {
                if (outstanding_sell_order.quantity >= order.quantity)
                {
                    outstanding_sell_order.quantity -= order.quantity;
                    if (outstanding_sell_order.quantity > 0)
                    {
                        orderbook->addOrder(outstanding_sell_order);
                    }
                    return;
                }
                order.quantity -= outstanding_sell_order.quantity;
                outstanding_sell_order.quantity = 0;
                outstanding_sell_order = orderbook->getSellOrders().top();
            }
            else
            {
                orderbook->addOrder(order);
                return;
            }
        }
    }

}