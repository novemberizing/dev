#ifndef   __X_REALITY__VARIABLE__HH__
#define   __X_REALITY__VARIABLE__HH__

#include <x/variable.hh>

namespace x
{
    namespace reality
    {
        template <typename T>
        class variable : public x::variable<T>
        {
        protected:  T __initial;
        protected:  T __current;
        protected:  x::real __interval;
        public:     inline const T & initial() const { return __initial; }
        public:     inline const T & current() const { return __current; }
        public:     virtual void update()
                    {
                        __current = this->__value;
                        __interval = 0.0f;
                    }
        public:     const T & value() const override { return this->__value; }
        public:     void value(const T & v) override
                    {
                        __interval = (__current == this->__value ? 0 : __interval/4);

                        __initial = __current;
                        __current = this->__value;

                        this->__value = v;
                    }
        public:     void value(T && v) override
                    {
                        __interval = (__current == this->__value ? 0 : __interval/4);

                        __initial = __current;
                        __current = this->__value;

                        this->__value = x::move(v);
                    }
        public:     x::reality::variable<T> & operator=(const x::reality::variable<T> & o)
                    {
                        if(&o != this)
                        {
                            x::variable<T>::operator=(o);
                            __initial = o.__initial;
                            __current = o.__current;
                            __interval = o.__interval;
                        }
                        return *this;
                    }
        public:     x::reality::variable<T> & operator=(x::reality::variable<T> && o) noexcept
                    {
                        if(&o != this)
                        {
                            x::variable<T>::operator=(x::move(o));
                            __initial = x::move(o.__initial);
                            __current = x::move(o.__current);
                            __interval = o.__interval;

                            o.__interval = 0;
                        }
                        return *this;
                    }
        public:     variable(const T & v)
                    :   x::variable<T>(v),
                        __initial(v),
                        __current(v),
                        __interval(0)
                    {
                    }
        public:     variable()
                    :   x::variable<T>(),
                        __initial(),
                        __current(),
                        __interval(0)
                    {
                    }
        public:     variable(const x::reality::variable<T> & o)
                    :   x::variable<T>(o),
                        __initial(o.__initial),
                        __current(o.__current),
                        __interval(o.__interval)
                    {
                    }
        public:     variable(x::reality::variable<T> && o) noexcept
                    :   x::variable<T>(x::move(o)),
                        __initial(x::move(o.__initial)),
                        __current(x::move(o.__current)),
                        __interval(o.__interval)
                    {
                        o.__interval = 0;
                    }
        public:     ~variable() override
                    {
                        __interval = 0;
                    }
        };
    }
}

#endif // __X_REALITY__VARIABLE__HH__
