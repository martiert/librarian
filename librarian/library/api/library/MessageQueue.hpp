#ifndef LIBRARY_MESSAGE_QUEUE_HPP
#define LIBRARY_MESSAGE_QUEUE_HPP

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

namespace library
{

template<typename M>
class MessageQueue
{
public:
    void send(M item)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(item);
        }
        cond_.notify_all();
    }

    M receive()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty())
            cond_.wait(lock, [this]() { return !queue_.empty(); });
        auto element = queue_.front();
        queue_.pop();
        return element;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<M> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;
};

}
#endif
