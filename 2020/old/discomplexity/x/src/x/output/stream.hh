#ifndef   __X_OUTPUT__STREAM__HH__
#define   __X_OUTPUT__STREAM__HH__

#include <x/type.hh>
#include <x/stream.hh>

namespace x
{
    namespace output
    {
        class stream : public x::stream<x::byte, x::byte>
        {
        public:     typedef stream & (*func)(stream &);
        protected:  x::byte pop() override
                    {
                        exceptional();
                    }
        public:     stream & operator<<(char v)
                    {
                        this->push(v);
                        return *this;
                    }
        public:     stream & operator<<(signed char v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%d", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(unsigned char v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%u", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(short v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%d", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(unsigned short v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%u", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(int v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%d", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(unsigned int v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%u", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(long v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%ld", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(unsigned long v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%lu", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(long long v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%lld", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(unsigned long long v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%llu", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(float v)
                    {
                        // TODO: IMPLEMENT THIS
                        char buffer[128];
                        int n = __snprintf(buffer, 128, "%f", v);
                        if(n > 0)
                        {
                            this->push((x::byte *) buffer, n);
                        }
                        return *this;
                    }
        public:     stream & operator<<(double v)
                    {
                        // TODO: IMPLEMENT THIS
                        return *this;
                    }
        public:     stream & operator<<(long double v)
                    {
                        // TODO: IMPLEMENT THIS
                        return *this;
                    }
        public:     stream & operator<<(const char * v)
                    {
                        if(v != nullptr)
                        {
                            this->push((x::byte *) v, __strlen(v));
                        }
                        return *this;
                    }
        public:     stream & operator<<(stream::func f)
                    {
                        if(f != nullptr)
                        {
                            f(*this);
                        }
                        return *this;
                    }
        public:     stream & operator=(const stream & o)
                    {
                        if(&o != this)
                        {
                            x::stream<x::byte, x::byte>::operator=(o);
                        }
                        return *this;
                    }
        public:     stream & operator=(stream && o) noexcept
                    {
                        if(&o != this)
                        {
                            x::stream<x::byte, x::byte>::operator=(x::move(o));
                        }
                        return *this;
                    }
        public:     stream()
                    :   x::stream<x::byte, x::byte>()
                    {
                    }
        public:     stream(const stream & o)
                    :   x::stream<x::byte, x::byte>(o)
                    {
                    }
        public:     stream(stream && o) noexcept
                    :   x::stream<x::byte, x::byte>(x::move(o))
                    {
                    }
        public:     ~stream() override
                    {
                    }
        };
    }



    inline x::output::stream & endl(x::output::stream & o)
    {
        o << '\n';
        return o;
    }
}

#endif // __X_OUTPUT__STREAM__HH__
