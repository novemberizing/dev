#ifndef   __X_GRAPHICS__UTIL__HH__
#define   __X_GRAPHICS__UTIL__HH__

#include <x/console.hh>

namespace x
{
    namespace graphics
    {
        namespace util
        {
            inline void unknown(const x::array<x::string> & strings)
            {
                x::console::out << "unknonw command => [";
                for(x::uint64 i = 0; i < strings.size(); i++)
                {
                    x::console::out << "\"" << strings[i] << "\"" << (i + 1 == strings.size() ? "" : ",");
                }
                x::console::out << "]" << x::endl;
            }

            extern x::float32 real32(const x::string & o);
            extern x::uint32 uinteger32(const x::string & o);
        }
    }
}

#endif // __X_GRAPHICS__UTIL__HH__
