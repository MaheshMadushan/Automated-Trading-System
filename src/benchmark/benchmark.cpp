#include <benchmark/benchmark.h>
#include "../matching/MatchingEngine.hpp"

static void BM_MatchingAlgorithmPriceTime(benchmark::State& state) {
  std::map<std::string, int> symbol_to_index_map{{"AAPL" , 1}};
  long instrumentIndex(1);
  MatchingEngine me{{instrumentIndex}};
  for (auto _ : state)
  {
    state.PauseTiming();
    auto order = orderbook::Order{state.range(0), state.range(1), 
          (int)state.range(2), state.range(3), static_cast<orderbook::Order::OrderType>(state.range(4))};
    state.ResumeTiming();
    me.matchOrder(order);
  }
}
// Register the function as a benchmark
BENCHMARK(BM_MatchingAlgorithmPriceTime)
                ->Args({400, 17, 10, 1, static_cast<int>(orderbook::Order::OrderType::BUY)})
                ->Args({400, 17, 10, 1, static_cast<int>(orderbook::Order::OrderType::SELL)});

BENCHMARK_MAIN();