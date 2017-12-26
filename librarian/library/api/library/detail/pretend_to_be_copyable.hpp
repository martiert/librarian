#ifndef LIBRARY_DETAIL_PRETEND_TO_BE_COPYABLE_HPP
#define LIBRARY_DETAIL_PRETEND_TO_BE_COPYABLE_HPP

namespace library
{

namespace detail
{

template<class T>
class pretend_to_be_copyable
{
public:
    explicit pretend_to_be_copyable(T && value)
        : value_(std::move(value))
    {}

    pretend_to_be_copyable(pretend_to_be_copyable const & other)
        : value_(std::move(other.value_))
    {}

    void operator()()
    {
        value_();
    }

private:
    mutable T value_;
};

}

}
#endif
