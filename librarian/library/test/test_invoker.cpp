#include "library/Invoker.hpp"

#include <catch/catch.hpp>

#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std::literals;

TEST_CASE("Invoking function", "[invoker]")
{
    std::mutex mutex;
    std::condition_variable cond;
    bool did_run = false;

    std::unique_lock<std::mutex> lock(mutex);

    library::Invoker invoker;
    invoker.execute([&did_run, &mutex, &cond]() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            did_run = true;
        }
        cond.notify_all();
    });

    cond.wait_for(lock, 500ms, [&did_run]() { return did_run; });
    REQUIRE(did_run);
}

TEST_CASE("Invoker returns future", "[invoker]")
{
    library::Invoker invoker;
    auto future = invoker.execute([]() { return 4; });
    REQUIRE(future.get() == 4);
}
