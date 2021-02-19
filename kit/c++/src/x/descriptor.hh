#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__HH__
#define   __NOVEMBERIZING_X__DESCRIPTOR__HH__

#include <x/std.hh>

namespace x
{
    class descriptor
    {
    public:     union handle
                {
                    x::int32 f;
                };
    public:     class event
                {
                public:     class generator
                            {
                            protected:  x::descriptor * head;
                            protected:  x::descriptor * tail;
                            protected:  x::uint64 size;
                            };
                };
    protected:  x::descriptor * prev;
    protected:  x::descriptor * next;
    protected:  x::descriptor::event::generator * generator;

    protected:  x::descriptor::handle handle;
    };
}

#endif // __NOVEMBERIZING_X__DESCRIPTOR__HH__
