#ifndef   __NOVEMBERIZING_X__ADDRESS__HH__
#define   __NOVEMBERIZING_X__ADDRESS__HH__

namespace x
{
    class address
    {
    public: template <typename T> static T * of(const T & o){ return static_cast<T *>(&o); }
    };
}

#endif // __NOVEMBERIZING_X__ADDRESS__HH__
