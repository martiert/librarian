#include "library/Library.hpp"
#include "library/Book.hpp"

namespace library
{

Library::Library(Database & database)
    : database_(database)
    , queue_(),
    , thread_(this::run)
    , stop_(false)
{}

Library::~Library()
{
    stop();
    thread_.join();
}

void Library::add_book(Book & book)
{
    queue_.push([&book, &database_]() {
        book.add_to_database(database_);
    });
}

void Library::stop()
{
    queue_.push([this]() { stop_ = true; })
}

void Library::run()
{
    std::function<void(void)> func;

    while (!stop) {
        if (queue_.pop(func)) {
            func();
        }
    }
}

}
