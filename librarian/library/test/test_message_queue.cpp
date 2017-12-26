#include "library/MessageQueue.hpp"

#include <catch/catch.hpp>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std::literals;

TEST_CASE("Empty queue", "[message queue]")
{
    library::MessageQueue<int> queue;

    SECTION("Initial queue is empty") {
        REQUIRE(queue.empty());
    }

    SECTION("Sending item to queue makes it non empty") {
        queue.send(2);
        REQUIRE_FALSE(queue.empty());
    }

    SECTION("Getting the single item from queue makes it empty again") {
        queue.send(2);
        queue.receive();
        REQUIRE(queue.empty());
    }
}

TEST_CASE("Sending and receiving a message", "[message queue]")
{
    library::MessageQueue<int> queue;
    queue.send(2);

    REQUIRE(queue.receive() == 2);
}

TEST_CASE("Receive is async", "[message queue]")
{
    std::mutex mutex;
    std::condition_variable cond;

    std::unique_lock<std::mutex> lock(mutex);

    bool thread_started = false;
    int n = 1;

    library::MessageQueue<int> queue;
    std::thread thread([&n, &queue, &mutex, &cond, &thread_started]() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            thread_started = true;
        }
        cond.notify_all();
        n = queue.receive();
    });

    cond.wait_for(lock, 500ms, [&thread_started]() { return thread_started; });
    REQUIRE(n == 1);

    queue.send(5);
    thread.join();

    REQUIRE(n == 5);
}
