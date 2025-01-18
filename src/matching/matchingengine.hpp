#include <unordered_map>
#include "../orderbook/OrderBook.hpp"

class MatchingEngine
{
    typedef long InstrumentIndex;
private:
    std::unordered_map<InstrumentIndex, orderbook::OrderBook*> instrument_to_order_books_map;
public:
    MatchingEngine() = default;

    // match order
    // try matchOrder
    void matchOrder(orderbook::Order& order);
};
