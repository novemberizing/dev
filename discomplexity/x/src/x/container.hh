#ifndef   __X__CONTAINER__HH__
#define   __X__CONTAINER__HH__

#include <x/type.hh>
#include <x/exception.hh>

namespace x
{
    /**
     * x::container is a class on which the data structure implementation class is based.
     *
     * Among the methods commonly used in all data structure classes,
     * and methods to be unrelated data type are declared as pure virtual functions.
     *
     * @since   0.0.1
     */
    class container
    {
    public:     virtual x::uint64 size() const = 0;
    public:     virtual x::boolean empty() const = 0;
    public:     x::container & operator=(const x::container & o) = delete;
    public:     x::container & operator=(x::container && o) noexcept = delete;
    /**
     *
     */
    protected:  container()
                {
                }
    public:     container(const x::container & o) = delete;
    public:     container(x::container && o) noexcept = delete;
    /**
     */
    public:     virtual ~container()
                {
                }
    };
}

#endif // __X__CONTAINER__HH__
