#include "buffer.hh"
#include "application.hh"

namespace x
{
    namespace graphics
    {
        buffer::buffer(x::uint32 target)
        :   __bytes(),
            __target(target),
            __usage(x::graphics::buffer::none),
            __id(0)
        {
        }

        buffer::buffer()
        :   __bytes(),
            __target(x::graphics::buffer::none),
            __usage(x::graphics::buffer::none),
            __id(0)
        {
        }

        buffer::buffer(const buffer & o)
        :   __bytes(o.__bytes),
            __target(o.__target),
            __usage(o.__usage),
            __id(o.__id)
        {
        }

        buffer::buffer(buffer && o) noexcept
        :   __bytes(x::move(o.__bytes)),
            __target(o.__target),
            __usage(o.__usage),
            __id(o.__id)
        {
            o.__target = x::graphics::buffer::none;
            o.__usage = x::graphics::buffer::none;
            o.__id = 0;
        }

        buffer::~buffer()
        {
        }

        buffer & buffer::operator=(const buffer & o)
        {
            if(&o != this)
            {
                __bytes = o.__bytes;
                __target = o.__target;
                __usage = o.__usage;
                __id = o.__id;
            }
            return *this;
        }

        buffer & buffer::operator=(buffer && o) noexcept
        {
            if(&o != this)
            {
                __bytes = x::move(o.__bytes);
                __target = o.__target;
                __usage = o.__usage;
                __id = o.__id;

                o.__target = x::graphics::buffer::none;
                o.__usage = x::graphics::buffer::none;
                o.__id = 0;
            }
            return *this;
        }

        void buffer::push(const x::graphics::vector & o)
        {
            push(o[0]);
            push(o[1]);
            push(o[2]);
            push(o[3]);
        }

        void buffer::push(const x::graphics::color & o)
        {
            push(o[0]);
            push(o[1]);
            push(o[2]);
            push(o[3]);
        }

        void buffer::push(const x::graphics::coordinate & o)
        {

            push(o[0]);
            push(o[1]);
        }

        void buffer::push(x::float32 v)
        {
            __bytes.push((x::byte *) &v, sizeof(x::float32));
        }
    }
}
