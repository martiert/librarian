#ifndef LIBRARY_BOOK_HPP
#define LIBRARY_BOOK_HPP

namespace library
{

class Database;

class Book
{
public:
    virtual void add_to_database(Database & db) = 0;
};

}
#endif
