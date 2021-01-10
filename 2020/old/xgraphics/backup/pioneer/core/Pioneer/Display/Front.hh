#ifndef   __PIONEER_DISPLAY__FRONT__HH__
#define   __PIONEER_DISPLAY__FRONT__HH__

#include <x/graphics/layer.hh>

namespace Pioneer
{
    namespace Display
    {
        class Front : public x::graphics::layer
        {
        public:     Pioneer::Display::Front & operator=(const Pioneer::Display::Front & o) = delete;
        public:     Pioneer::Display::Front & operator=(Pioneer::Display::Front && o) noexcept = delete;
        public:     Front(const x::string & name);
        public:     Front() = delete;
        public:     Front(const Pioneer::Display::Front & o) = delete;
        public:     Front(Pioneer::Display::Front && o) noexcept = delete;
        public:     ~Front() override;
        };
    }
}

#endif // __PIONEER_DISPLAY__FRONT__HH__
