#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

namespace orderbook
{

    enum class OrderType : int
    {
        SELL = 0,
        BUY = 1
    };

    struct Order
    {
        long time_stamp;
        long quantity;
        long instrument; // read size from configs
        OrderType order_type;
    };

    struct OrderKey
    {
        long time_stamp;
        long quantity;
        long instrument; // read size from configs
        OrderType order_type;
        OrderKey(const Order order)
        {
            time_stamp = order.time_stamp;
            quantity = order.quantity;
            instrument = order.instrument;
            order_type = order.order_type;
        }
        
        bool operator==(const OrderKey &other) const noexcept
        {
            return (this->time_stamp == other.time_stamp &&
                    this->quantity == other.quantity &&
                    this->instrument == other.instrument &&
                    this->order_type == other.order_type);
        }
    };

    // think abouth the hash function
    struct OrderHash
    {
        std::size_t operator()(const OrderKey& orderKey) const noexcept
        {
            std::size_t h1 = std::hash<long>{}(orderKey.instrument);
            std::size_t h2 = std::hash<long>{}(orderKey.quantity);
            std::size_t h3 = std::hash<int>{}(static_cast<int>(orderKey.order_type));
            std::size_t h4 = std::hash<long>{}(orderKey.time_stamp);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 4); // or use boost::hash_combine
        }
    };

    // template <class Order>
    class OrderBook
    {
    private:
        std::unordered_map<orderbook::OrderKey, Order, OrderHash> orders; // let's think about hashing
    public:
        OrderBook();

        OrderBook(const OrderBook &other) = delete;      // no copying
        OrderBook(OrderBook &) = delete;                 // no non-const copying
        OrderBook &operator=(const OrderBook &) = delete; // no copy assignment

        OrderBook(OrderBook &&other) = delete;            // no moving
        OrderBook &operator=(OrderBook &&other) = delete; // no move assignment

        inline void addOrder(const Order order)
        {
            const orderbook::OrderKey orderKey(order);
            // orders.emplace(std::make_pair(orderKey, std::make_shared<Order>(order)));
            orders.emplace(std::make_pair(orderKey, order));
            // matching engine call back
        }

        void removeOrder(const Order order_to_remove)
        {
        }
    };

} // namespace orderbook

// wisdom - The difference between move and copy is that after a copy two objects must have the same value, whereas after a move the source of the move is not required to have its original value.
#endif