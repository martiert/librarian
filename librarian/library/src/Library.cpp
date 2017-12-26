#include "library/Library.hpp"
#include "library/Book.hpp"

namespace library
{

Library::Library(Database & database)
    : database_(database)
{}

Library::~Library()
{
}

std::future<bool> Library::add_book(Book & book)
{
    return invoker_.execute([&book, this]() {
        return book.add_to_database(database_);
    });
}

}
