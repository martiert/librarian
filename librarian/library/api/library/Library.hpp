#ifndef LIBRARY_LIBRARY_HPP
#define LIBRARY_LIBRARY_HPP

#include <boost/lockfree/queue.hpp>

#include <thread>

namespace library
{

class Database;
class Book;

class Library
{
public:
    Library(Database & database);

    void stop();
    void add_book(Book & book);

private:
    void run();

    Database & database_;
    boost::lockfree::queue<void (*)(void)> queue_;
    bool stop_;
    std::thread thread_;
};

}

#endif
