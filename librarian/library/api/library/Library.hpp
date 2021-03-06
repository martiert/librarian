#ifndef LIBRARY_LIBRARY_HPP
#define LIBRARY_LIBRARY_HPP

#include "library/Invoker.hpp"

#include <future>

namespace library
{

class Database;
class Book;

class Library
{
public:
    explicit Library(Database & database);

    std::future<bool> add_book(Book & book);

private:
    Database & database_;
    Invoker invoker_;
};

}

#endif
