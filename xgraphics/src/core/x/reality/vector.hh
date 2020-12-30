#ifndef   __X_REALITY__VECTOR__HH__
#define   __X_REALITY__VECTOR__HH__

#include <x/vector.hh>
#include <x/string.hh>
#include <x/real32.hh>
#include <x/console.hh>

namespace x
{
    namespace reality
    {
        class vector : protected x::vector<x::real>
        {
        public:     static const x::reality::vector center;
        public:     static const x::reality::vector up;
        public:     static const x::reality::vector front;
        public:     static const x::reality::vector zero;
        public:     static const x::reality::vector one;
        public:     static x::reality::vector radian(const x::reality::vector & o);
        public:     static x::reality::vector degree(const x::reality::vector & o);
        public:     static x::reality::vector normalize(const x::reality::vector & o);
        public:     static x::reality::vector cross(const x::reality::vector & x, const x::reality::vector & y);
        public:     static x::real dot(const x::reality::vector & x, const x::reality::vector & y);
        public:     inline const x::real * data() const { return x::vector<x::real>::data(); }
        public:     inline const x::real & x() const { return x::vector<x::real>::operator[](0); }
        public:     inline const x::real & y() const { return x::vector<x::real>::operator[](1); }
        public:     inline const x::real & z() const { return x::vector<x::real>::operator[](2); }
        public:     inline const x::real & w() const { return x::vector<x::real>::operator[](3); }
        public:     inline void x(x::real v){ x::vector<x::real>::operator[](0) = v; }
        public:     inline void y(x::real v){ x::vector<x::real>::operator[](1) = v; }
        public:     inline void z(x::real v){ x::vector<x::real>::operator[](2) = v; }
        protected:  inline void w(x::real v){ x::vector<x::real>::operator[](3) = v; }
        public:     virtual void set(x::real x, x::real y, x::real z, x::real w);
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index, function<x::real (x::real)> in, function<x::real (x::real)> out);
        public:     inline const x::real & operator[](x::uint64 i) const { return x::vector<x::real>::operator[](i); }
        public:     inline x::real & operator[](x::uint64 i) { return x::vector<x::real>::operator[](i); }
        public:     x::reality::vector & operator-=(const x::reality::vector & o);
        public:     x::reality::vector & operator+=(const x::reality::vector & o);
        public:     x::reality::vector & operator*=(const x::real & v);
        public:     x::reality::vector & operator=(const x::initializer<x::real> & list);
        public:     x::reality::vector & operator=(const x::reality::vector & o);
        public:     x::reality::vector & operator=(x::reality::vector && o) noexcept;
        public:     vector(const x::reference<x::array<x::real> > reference, x::uint64 offset, x::uint64 length);
        public:     vector(x::array<x::real> && o);
        public:     vector(x::real x, x::real y, x::real z);
        public:     vector(x::real x, x::real y, x::real z, x::real w);
        public:     vector(const x::initializer<x::real> & list);
        public:     vector(const x::initializer<x::real> & list, x::real w);
        public:     vector();
        public:     vector(const x::reality::vector & o);
        public:     vector(x::reality::vector && o) noexcept;
        public:     ~vector() override;
        public:     friend x::reality::vector operator*(const x::reality::vector & x, x::real y)
                    {
                        x::reality::vector result = x;
                        result *= y;
                        return result;
                    }
        public:     friend x::reality::vector operator*(x::real x, const x::reality::vector & y)
                    {
                        x::reality::vector result = y;
                        result *= x;
                        return result;
                    }
        public:     friend x::reality::vector operator+(const x::reality::vector & x, const x::reality::vector & y)
                    {
                        assertion(x.__length != y.__length || x.__length == 0);

                        x::reality::vector result = x;
                        result += y;
                        return result;
                    }
        public:     friend x::reality::vector operator-(const x::reality::vector & x, const x::reality::vector & y)
                    {
                        assertion(x.__length != y.__length || x.__length == 0);

                        x::reality::vector result = x;
                        result -= y;
                        return result;
                    }
        public:     friend bool operator!=(const x::reality::vector & x, const x::reality::vector & y)
                    {
                        if(x.__length == y.__length)
                        {
                            for(x::uint64 i = 0; i < x.__length; i++)
                            {
                                if(x[i] != y[i])
                                {
                                    return true;
                                }
                            }
                            return false;
                        }
                        return true;
                    }
        public:     friend bool operator==(const x::reality::vector & x, const x::reality::vector & y)
                    {
                        if(x.__length == y.__length)
                        {
                            for(x::uint64 i = 0; i < x.__length; i++)
                            {
                                if(x[i] != y[i])
                                {
                                    return false;
                                }
                            }
                            return true;
                        }
                        return false;
                    }
        public:     friend x::output::stream & operator<<(x::output::stream & os, const x::reality::vector & o)
                    {
                        os << "["
                           << o[0] << ","
                           << o[1] << ","
                           << o[2] << ","
                           << o[3]
                           << "]";
                        return os;
                    }
        };
    }
}

#endif // __X_REALITY__VECTOR__HH__
