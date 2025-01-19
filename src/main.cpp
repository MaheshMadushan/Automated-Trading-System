#include <iostream>
#include "matching/MatchingEngine.hpp"
#include <chrono>

/*
Defining life of an order and trade

order -> matching engine -> *process -> order not matched -> put all/remaining on the order book
                            |                                           A
                            v                                           |
                            order matched -> partially fullfilled -------
                            |                       |
                            v                       |
                            fullfilled              | (async)
                            |                       |
                            v             (async)   v
                            trade done ---------> post trade activities (async)
                            |
                            v
                            update order book
*/

int main() {
    // start matching engine thread
    orderbook::Order incoming_order;
    MatchingEngine me({1});
    while (true)
    {
        std::cout << "Enter price, quantity and order type for AAPL (index = 1) instrument\n";
        std::cout << "Buy (2) or Sell (1) order ?\n";
        int order_type;
        std::cin >> order_type;
        incoming_order.order_type = static_cast<orderbook::Order::OrderType>(order_type-1);
        std::cout << "Price ?\n";
        std::cin >> incoming_order.price;
        std::cout << "Quantity ?\n";
        std::cin >> incoming_order.quantity;
        const auto now     = std::chrono::system_clock::now();
        const auto epoch   = now.time_since_epoch();
        incoming_order.time_stamp = epoch.count();
        incoming_order.instrument = 1;
        
        me.matchOrder(incoming_order);

        std::vector<orderbook::Order> asks;
        std::vector<orderbook::Order> bids;
        me.getOrderBook(1)->getOrderBookCurrentSnapshot(asks, bids);

        std::cout << "\n==============OrderBook Snapshot==============\n";
        auto it = asks.rbegin();
        while (it != asks.rend())
        {
            it->toString();
            it++;
        }
        std::cout << "==============================================\n";
        for (auto& bid : bids)
        {
            bid.toString();
        }
        std::cout << "==============================================\n\n";
    }

}