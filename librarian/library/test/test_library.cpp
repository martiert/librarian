#include <catch/catch.hpp>

#include "library/Database.hpp"
#include "library/Book.hpp"
#include "library/Library.hpp"

class DatabaseStub : public library::Database
{
};

class StubBook : public library::Book
{
public:
    StubBook()
        : database(nullptr)
    {}

    bool add_to_database(library::Database & db) override
    {
        database = &db;
        return true;
    }

    library::Database * database;
};

TEST_CASE("add book uses correct database class", "[library]")
{
    DatabaseStub db;
    library::Library lib(db);

    StubBook book;

    lib.add_book(book).get();

    REQUIRE(book.database == &db);
}
