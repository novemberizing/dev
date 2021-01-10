#ifndef   __X_REALITY__REFERENCE__HH__
#define   __X_REALITY__REFERENCE__HH__

#include <x/string.hh>

namespace x
{
    namespace reality
    {
        class reference
        {
        protected:  static const x::string __noname;
        public:     virtual const x::string & name() const { return __noname; }
        public:     x::reality::reference & operator=(const x::reality::reference & o) = delete;
        public:     x::reality::reference & operator=(x::reality::reference && o) noexcept = delete;
        public:     reference();
        public:     reference(const x::reality::reference & o) = delete;
        public:     reference(x::reality::reference && o) noexcept = delete;
        public:     virtual ~reference();
        };
    }
}

#endif // __X_REALITY__REFERENCE__HH__
