#ifndef LIBRARY_INVOKER_HPP
#define LIBRARY_INVOKER_HPP

#include "library/MessageQueue.hpp"
#include "library/detail/pretend_to_be_copyable.hpp"

#include <functional>
#include <future>
#include <thread>

namespace library
{

class Invoker
{
public:
    Invoker()
        : done_(false)
        , thread_(&Invoker::run, this)
    {}

    ~Invoker()
    {
        queue_.send([this]() { stop(); });
        thread_.join();
    }

    template<class Function>
    std::future<typename std::result_of<Function()>::type> execute(Function && func)
    {
        using result_type = typename std::result_of<Function()>::type;
        using task_type = std::packaged_task<result_type()>;

        task_type task(std::forward<Function>(func));
        auto future = task.get_future();

        queue_.send(detail::pretend_to_be_copyable<task_type>(std::move(task)));
        return future;
    }

private:

    void stop()
    {
        done_ = true;
    }

    void run()
    {
        while (!done_)
            queue_.receive()();
    }

    bool done_;
    MessageQueue<std::function<void(void)>> queue_;
    std::thread thread_;
};

}
#endif
