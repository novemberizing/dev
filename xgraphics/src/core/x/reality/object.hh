#ifndef   __X_REALITY__OBJECT__HH__
#define   __X_REALITY__OBJECT__HH__

#include <x/string.hh>
#include <x/reality/matrix.hh>
#include <x/reality/camera.hh>
#include <x/reality/event.hh>
#include <x/reality/reference.hh>

namespace x
{
    namespace reality
    {
        class object
        {
        protected:  static const x::string __noname;
        public:     virtual x::reality::reference * reality() { return nullptr; }
        public:     virtual const x::string & name() const { return __noname; }
        public:     virtual const x::reality::vector & position() const { return x::reality::vector::center; }
        public:     virtual const x::reality::vector & front() const { return x::reality::vector::front; }
        public:     virtual const x::reality::vector & up() const { return x::reality::vector::up; }
        public:     virtual x::real mass() const { return 0.0f; }
        public:     virtual x::boolean on(const x::reality::event & event) {}
        public:     x::reality::object & operator=(const x::reality::object & o) = delete;
        public:     x::reality::object & operator=(x::reality::object && o) noexcept = delete;
        protected:  object();
        public:     object(const x::reality::object & o) = delete;
        public:     object(x::reality::object && o) noexcept = delete;
        public:     virtual ~object();
        };
    }
}

#endif // __X_REALITY__OBJECT__HH__
