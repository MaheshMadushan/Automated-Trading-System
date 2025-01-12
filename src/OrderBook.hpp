#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory.h>

enum class OrderType : int {
    SELL = 0,
    BUY = 1
};

struct Order
{
   long time_stamp;
   long quantity;
   std::string instrument; // read size from configs
   OrderType order_type;
};

struct OrderKey
{
    long time_stamp;
    long quantity;
    std::string instrument; // read size from configs
    OrderType order_type;
    OrderKey(const Order order) {
        time_stamp = order.time_stamp;
        quantity = order.quantity;
        instrument = order.instrument;
        order_type = order.order_type;
    }
    bool operator==(const OrderKey& other) {
        return (this->time_stamp == other.time_stamp &&
                this->quantity == other.quantity &&
                this->instrument == other.instrument &&
                this->order_type == other.order_type);
    }
};


template <class Order>
class OrderBook
{
private:
    std::unordered_map<OrderKey, std::shared_ptr<Order>> orders; // let's think about hashing
public:
    OrderBook();

    OrderBook(const OrderBook& other) = delete; // no copying
    OrderBook(OrderBook&) = delete; // no non-const copying
    OrderBook& operator=(const OderBook&) = delete; // no copy assignment
    
    OrderBook(OrderBook&& other) = delete; // no moving
    OrderBook& operator=(OrderBook&& other) = delete; // no move assignment

    void addOrder(const Order order) {
        orders.push_back(order);
        // matching engine call back
    }

    void removeOrder(const Order order_to_remove) {
        
    }
};
// wisdom - The difference between move and copy is that after a copy two objects must have the same value, whereas after a move the source of the move is not required to have its original value. 
#endif