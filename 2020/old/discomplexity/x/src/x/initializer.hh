#ifndef   __X__INITIALIZER__HH__
#define   __X__INITIALIZER__HH__

#include <initializer_list> // REMOVE THIS

namespace x
{
    template <typename T> using initializer = std::initializer_list<T>;
}

#endif // __X__INITIALIZER__HH__
