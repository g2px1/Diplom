//#include <iostream>
//
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}

//#include <benchmark/benchmark.h>
//#include <vector>
//
//static void BM_VectorInsertion(benchmark::State& state) {
//    for (auto _ : state) {
//        std::vector<int> v;
//        v.reserve(state.range(0)); // Avoid reallocations to focus on the push_back operation
//
//        for (int i = 0; i < state.range(0); ++i) {
//            benchmark::DoNotOptimize(i);
//        }
//    }
//    state.SetComplexityN(state.range(0));
//}
//
//// Register the benchmark
//BENCHMARK(BM_VectorInsertion)
//        ->Range(8, 8<<10) // Test a range from 8 to 8192 elements
//        ->Complexity(benchmark::oAuto);
//
//BENCHMARK_MAIN();

//#include <benchmark/benchmark.h>
//#include <map>
//
//static void BM_MapInsertion(benchmark::State& state) {
//    for (auto _ : state) {
//        state.PauseTiming();
//        std::map<int, int> m;
//        state.ResumeTiming();
//
//        for (int i = 0; i < state.range(0); ++i) {
//            benchmark::DoNotOptimize(m.insert(std::make_pair(i, i)));
//        }
//    }
//    state.SetComplexityN(state.range(0));
//}
//
//// Register the benchmark
//BENCHMARK(BM_MapInsertion)
//        ->RangeMultiplier(2)->Range(8, 8<<10) // Test a range from 8 to 8192 elements, doubling each time
//        ->Complexity(benchmark::oAuto); // Expecting logarithmic complexity
//
//BENCHMARK_MAIN();

#include <benchmark/benchmark.h>
#include <cds/init.h>           // for cds::Initialize and cds::Terminate
#include <cds/gc/hp.h>          // for Hazard Pointer (HP) garbage collection
#include <cds/threading/model.h>   // for thread attachments

#if MSQUEUE_TEST
#include <cds/container/msqueue.h> // Michael & Scott lock-free queue

// Alias for the queue type using Hazard Pointer (HP) garbage collection
using Queue = cds::container::MSQueue<cds::gc::HP, int>;

class MSQueueFixture : public benchmark::Fixture {
public:
    cds::gc::HP hpGC; // Hazard Pointer GC instance
    Queue* queue;     // Pointer to the queue

    MSQueueFixture() {
        cds::Initialize(); // Initialize libcds
        cds::gc::hp::GarbageCollector::Construct(16, // max thread count
                                                 1,  // max retired pointer count per thread
                                                 16); // enable dynamic HP allocation if needed
        cds::threading::Manager::attachThread(); // Attach main thread
    }

    void SetUp(const ::benchmark::State& state) {
        queue = new Queue(); // Create an instance of the queue
    }

    void TearDown(const ::benchmark::State& state) {
        delete queue; // Clean up the queue
    }

    ~MSQueueFixture() {
        cds::threading::Manager::detachThread(); // Detach main thread
        cds::Terminate(); // Terminate libcds
    }
};

BENCHMARK_DEFINE_F(MSQueueFixture, Enqueue)(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            queue->enqueue(i);
        }
        // Cleanup after benchmark loop
        int dummy;
        while (queue->dequeue(dummy)) {
            // Dequeue all elements to avoid memory leak
        }
    }
}

BENCHMARK_DEFINE_F(MSQueueFixture, Dequeue)(benchmark::State& state) {
    // Pre-fill the queue with elements
    for (int i = 0; i < state.range(0); ++i) {
        queue->enqueue(i);
    }

    for (auto _ : state) {
        int value;
        for (int i = 0; i < state.range(0); ++i) {
            if (!queue->dequeue(value)) {
                state.SkipWithError("Dequeue failed");
                break;
            }
        }
        // Re-fill the queue for the next iteration, outside the timed section
        if (state.iterations() >= 0) { // Check if the benchmark is not finished
            for (int i = 0; i < state.range(0); ++i) {
                queue->enqueue(i);
            }
        }
    }
}

// Register the function as a benchmark
BENCHMARK_REGISTER_F(MSQueueFixture, Enqueue)->Range(8, 8<<10)->Complexity(benchmark::oAuto);
BENCHMARK_REGISTER_F(MSQueueFixture, Dequeue)->Range(8, 8<<10)->Complexity(benchmark::oAuto);

BENCHMARK_MAIN();

#endif

#if BUCKETQUEUE_TEST
#include <cds/container/basket_queue.h>

using Queue = cds::container::BasketQueue<cds::gc::HP, int>;

class BasketQueueFixture : public benchmark::Fixture {
public:
    cds::gc::HP hpGC; // Hazard Pointer GC instance
    Queue* queue;     // Pointer to the queue

    BasketQueueFixture() {
        cds::Initialize(); // Initialize libcds
        cds::gc::hp::GarbageCollector::Construct(16, // max thread count
                                                 1,  // max retired pointer count per thread
                                                 16); // enable dynamic HP allocation if needed
        cds::threading::Manager::attachThread(); // Attach main thread
    }

    void SetUp(const ::benchmark::State& state) {
        queue = new Queue(); // Create an instance of the queue
    }

    void TearDown(const ::benchmark::State& state) {
        delete queue; // Clean up the queue
    }

    ~BasketQueueFixture() {
        cds::threading::Manager::detachThread(); // Detach main thread
        cds::Terminate(); // Terminate libcds
    }
};

BENCHMARK_DEFINE_F(BasketQueueFixture, Enqueue)(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            queue->enqueue(i);
        }
        // Cleanup after benchmark loop
        int dummy;
        while (queue->dequeue(dummy)) {
            // Dequeue all elements to avoid memory leak
        }
    }
}

BENCHMARK_DEFINE_F(BasketQueueFixture, Dequeue)(benchmark::State& state) {
    // Pre-fill the queue with elements
    for (int i = 0; i < state.range(0); ++i) {
        queue->enqueue(i);
    }

    for (auto _ : state) {
        int value;
        for (int i = 0; i < state.range(0); ++i) {
            if (!queue->dequeue(value)) {
                state.SkipWithError("Dequeue failed");
                break;
            }
        }
        // Re-fill the queue for the next iteration, outside the timed section
        if (state.iterations() >= 0) { // Check if the benchmark is not finished
            for (int i = 0; i < state.range(0); ++i) {
                queue->enqueue(i);
            }
        }
    }
}

// Register the function as a benchmark
BENCHMARK_REGISTER_F(BasketQueueFixture, Enqueue)->Range(8, 8<<10)->Complexity(benchmark::oAuto);
BENCHMARK_REGISTER_F(BasketQueueFixture, Dequeue)->Range(8, 8<<10)->Complexity(benchmark::oAuto);

BENCHMARK_MAIN();

#endif

#if BRONSONTREE_TEST

#include <benchmark/benchmark.h>
#include <cds/init.h>
#include <cds/urcu/general_buffered.h>
#include <cds/container/bronson_avltree_map_rcu.h>

using namespace cds::urcu;
using namespace cds::container;

// Define RCU type and map type
using rcu_gpb = cds::urcu::gc<general_buffered<>>;
using Map = BronsonAVLTreeMap<rcu_gpb, int, int>;

class AVLMapFixture : public benchmark::Fixture {
public:
    Map* map;

    AVLMapFixture() {
        cds::Initialize();
    }

    void SetUp(const ::benchmark::State&) {
        // Initialize RCU before using the map
        cds::gc::hp::smr::construct();
        map = new Map();
    }

    void TearDown(const ::benchmark::State&) {
        delete map;
        // Clean up RCU after done using the map
        cds::gc::hp::smr::destruct();
    }

    ~AVLMapFixture() {
        cds::Terminate();
    }
};

BENCHMARK_DEFINE_F(AVLMapFixture, Insert)(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            map->insert(i, i);
        }
        // Cleanup after benchmark loop
        for (int i = 0; i < state.range(0); ++i) {
            map->erase(i);
        }
    }
}

BENCHMARK_DEFINE_F(AVLMapFixture, Find)(benchmark::State& state) {
    // Pre-fill the map with elements
    for (int i = 0; i < state.range(0); ++i) {
        map->insert(i, i);
    }

    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            typename Map::value_type* val = nullptr;
            map->find(i, [&val](typename Map::value_type& found) { val = &found; });
        }
    }

    // Cleanup after benchmark loop
    for (int i = 0; i < state.range(0); ++i) {
        map->erase(i);
    }
}

// Register the function as a benchmark
BENCHMARK_REGISTER_F(AVLMapFixture, Insert)->Range(8, 8<<10)->Complexity(benchmark::oAuto);
BENCHMARK_REGISTER_F(AVLMapFixture, Find)->Range(8, 8<<10)->Complexity(benchmark::oAuto);

BENCHMARK_MAIN();
#endif