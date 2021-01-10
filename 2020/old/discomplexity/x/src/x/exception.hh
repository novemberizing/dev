#ifndef   __X__EXCEPTION__HH__
#define   __X__EXCEPTION__HH__

#include <exception>    // TODO: REMOVE THIS
#include <x/function.hh>

namespace x
{
    class exception : public std::exception
    {
    public:     template <typename T> static void safe(x::function<void (T)> f, T o)
                {
                    if(f)
                    {
                        try
                        {
                            f(o);
                        }
                        catch(const x::exception & e)
                        {

                        }
                    }
                }
    public:     template <typename T, typename U> static void safe(x::function<void (T, U)> f, T first, U second)
                {
                    if(f)
                    {
                        try
                        {
                            f(first, second);
                        }
                        catch(const x::exception & e)
                        {

                        }
                    }
                }
    public:     const char * what() const noexcept override
                {
                    return "exception";
                }
    public:     x::exception & operator=(const x::exception & o)
                {
                    if(&o != this)
                    {
                    }
                    return *this;
                }
    public:     x::exception & operator=(x::exception && o) noexcept
                {
                    if(&o != this)
                    {
                    }
                    return *this;
                }
    public:     exception()
                {
                }
    public:     exception(const x::exception & o)
                {
                }
    public:     exception(x::exception && o) noexcept
                {
                }
    public:     ~exception() override
                {
                }
    };
}

#if 1
//     console::out << __FILE__ << ":" << __LINE__ << " => " << __func__ << endl;
#define exceptional() do {                                                              \
    __console_out(__FILE__);                                                            \
    __console_out(":");                                                                 \
    __console_out(__LINE__);                                                            \
    __console_out("\n");                                                                \
    throw x::exception();                                                               \
} while(0)
#else
#define exceptional() do {                                                              \
    throw x::exception();                                                               \
} while(0)
#endif

// console::out << __FILE__ << ":" << __LINE__ << " => " << __func__ << endl;
#define assertion(condition) do {                                                       \
    if(condition)                                                                       \
    {                                                                                   \
        throw x::exception();                                                           \
    }                                                                                   \
} while(0)

#endif // __X__EXCEPTION__HH__
