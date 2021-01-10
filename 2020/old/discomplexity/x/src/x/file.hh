#ifndef   __X__FILE__HH__
#define   __X__FILE__HH__

#include <x/string.hh>
#include <x/bytes.hh>
#include <x/input/stream.hh>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace x
{
    class file
    {
    public:     class input
                {
                public:     class stream : protected array<byte>
                            {
                            public:     static x::file::input::stream open(const char * path)
                                        {
                                            x::file::input::stream in;
                                            in.__descriptor = ::open(path, O_RDONLY);
                                            if(in.__descriptor < 0)
                                            {
                                                exceptional();
                                            }
                                            return in;
                                        }
                            protected:  x::int32 __descriptor;
                            public:     virtual x::int32 finish() const
                                        {
                                            uint64 offset = lseek(__descriptor, 0, SEEK_CUR);
                                            uint64 last   = lseek(__descriptor, 0, SEEK_END);
                                            lseek(__descriptor, offset, SEEK_SET);
                                            return offset == last ? 1 : 0;
                                        }
                            public:     x::float32 real32() const
                                        {
                                            x::float32 result = 0;
                                            this->read((byte *) &result, sizeof(x::float32));
                                            return result;
                                        }
                            public:     x::float64 real64() const
                                        {
                                            x::float64 result = 0;
                                            this->read((byte *) &result, sizeof(x::float64));
                                            return result;
                                        }
                            public:     x::uint8 uinteger8() const
                                        {
                                            x::uint8 result = 0;
                                            this->read((byte *) &result, sizeof(x::uint8));
                                            return result;
                                        }
                            public:     x::uint16 uinteger16() const
                                        {
                                            x::uint16 result = 0;
                                            this->read((byte *) &result, sizeof(x::uint16));
                                            return result;
                                        }
                            public:     x::uint32 uinteger32() const
                                        {
                                            x::uint32 result = 0;
                                            this->read((byte *) &result, sizeof(x::uint32));
                                            return result;
                                        }
                            public:     x::string str(x::uint64 n) const
                                        {
                                            char * result = memory::allocate<char>(n + 2);
                                            this->read((byte*)result, n);
                                            return x::string(x::move(result), n);
                                        }
                            public:     x::bytes data(x::uint64 n) const
                                        {
                                            byte * result = memory::allocate<byte>(n + 2);
                                            this->read(result, n);
                                            return x::bytes(x::move(result), n);
                                        }
                            public:     void read(x::byte * out, x::uint64 size) const
                                        {
                                            x::int64 n = ::read(__descriptor, out, size);
                                            if(n != size)
                                            {
                                                exceptional();
                                            }
                                        }
                            public:     x::file::input::stream & operator=(const x::file::input::stream & o) =  delete;
                            public:     x::file::input::stream & operator=(x::file::input::stream && o) noexcept
                                        {
                                            if(&o != this)
                                            {
                                                x::array<byte>::operator=(x::move(o));
                                                __descriptor = o.__descriptor;

                                                o.__descriptor = -1;
                                            }
                                            return *this;
                                        }
                            public:     stream() :
                                            x::array<byte>(),
                                            __descriptor(-1)
                                        {
                                        }
                            public:     stream(const x::file::input::stream & o) = delete;
                            public:     stream(x::file::input::stream && o) noexcept :
                                            x::array<byte>(x::move(o)),
                                            __descriptor(o.__descriptor)
                                        {
                                            o.__descriptor = 0;
                                        }
                            public:     ~stream()
                                        {
                                            if(__descriptor != -1)
                                            {
                                                ::close(__descriptor);
                                                __descriptor = -1;
                                            }
                                        }
                            };
                };
    protected:  x::string __path;
    public:     file & operator=(const file & o)
                {
                    if(&o != this)
                    {
                        __path = o.__path;
                    }
                    return *this;
                }
    public:     file & operator=(file && o) noexcept
                {
                    if(&o != this)
                    {
                        __path = x::move(o.__path);
                    }
                    return *this;
                }
    public:     file() :
                    __path()
                {
                }
    public:     file(const file & o) :
                    __path(o.__path)
                {
                }
    public:     file(file && o) noexcept :
                    __path(x::move(o.__path))
                {
                }
    public:     virtual ~file()
                {
                }
    };
}

#endif // __X__FILE__HH__
