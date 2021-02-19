#ifndef   __NOVEMBERIZING_X__CONTAIER__HH__
#define   __NOVEMBERIZING_X__CONTAIER__HH__

#include <x/std.hh>
#include <x/address.hh>

namespace x
{
    class container
    {
    protected:  x::uint64 _size;
    public:     virtual void clear(void) = 0;
    public:     virtual x::int32 empty(void) const { return _size == 0; }
    public:     virtual x::uint64 size(void) const { return _size; }
    public:     x::container & operator=(const x::container & o) = delete;
    public:     x::container & operator=(x::container && o) noexcept = delete;
    public:     container(void) : _size(0L) {}
    public:     container(const x::container & o) : _size(o._size) {}
    public:     container(x::container && o) noexcept : _size(o._size)
                {
                    o._size = 0;
                }
    public:     virtual ~container(void)
                {
                    this->_size = 0;
                }
    };
}

#endif // __NOVEMBERIZING_X__CONTAIER__HH__