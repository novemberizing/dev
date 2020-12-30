#ifndef   __X_GRAPHICS__VECTOR__HH__
#define   __X_GRAPHICS__VECTOR__HH__

#include <x/graphics/type.hh>
#include <x/graphics/util.hh>

namespace x
{
    namespace graphics
    {
        class vector : protected x::vector<x::float32>
        {
        public:     static x::graphics::vector degree(const x::graphics::vector & o)
                    {
                        x::graphics::vector result;
                        result[0] = x::math::degree(o.x());
                        result[1] = x::math::degree(o.y());
                        result[2] = x::math::degree(o.z());
                        result[3] = x::math::degree(o.w());
                        return result;
                    }
        public:     static x::graphics::vector normalize(const x::graphics::vector & o)
                    {
                        x::float32 dot = x::math::sqrt<x::float32>(x::graphics::vector::dot(o, o));
                        const array<x::float32> & container = o.__reference.get();
                        array<x::float32> result;
                        for(x::uint64 i = 0; i < o.__length; i++)
                        {
                            result.push(container[o.__offset + i] / dot);
                        }
                        return x::graphics::vector(x::move(result));
                    }
        public:     static x::graphics::vector cross(const x::graphics::vector & x, const x::graphics::vector & y)
                    {
                        assertion(x.__length != y.__length || x.__length < 3);
                        x::graphics::vector result;
                        result[0] = (x[1] * y[2] - x[2] * y[1]);
                        result[1] = (x[2] * y[0] - x[0] * y[2]);
                        result[2] = (x[0] * y[1] - x[1] * y[0]);
                        return result;
                    }
        public:     static x::float32 dot(const x::graphics::vector & x, const x::graphics::vector & y)
                    {
                        assertion(x.__length != y.__length || x.__length == 0);
                        x::float32 result = x[0] * y[0];
                        for(x::uint64 i = 1; i < x.__length; i++)
                        {
                            result += (x[i] * y[i]);
                        }
                        return result;
                    }
        public:     inline const x::float32 * data() const
                    {
                        return x::vector<x::float32>::data();
                    }
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index, function<float32 (float32)> in, function<float32 (float32)> out);
        public:     inline const x::float32 & x() const { return x::vector<x::float32>::operator[](0); }
        public:     inline const x::float32 & y() const { return x::vector<x::float32>::operator[](1); }
        public:     inline const x::float32 & z() const { return x::vector<x::float32>::operator[](2); }
        public:     inline const x::float32 & w() const { return x::vector<x::float32>::operator[](3); }
        public:     inline void x(x::float32 v){ x::vector<x::float32>::operator[](0) = v; }
        public:     inline void y(x::float32 v){ x::vector<x::float32>::operator[](1) = v; }
        public:     inline void z(x::float32 v){ x::vector<x::float32>::operator[](2) = v; }
        protected:  inline void w(x::float32 v){ x::vector<x::float32>::operator[](3) = v; }
        public:     virtual void set(x::float32 x, x::float32 y, x::float32 z, x::float32 w);
        public:     inline const x::float32 & operator[](x::uint64 i) const { return x::vector<x::float32>::operator[](i); }
        public:     inline x::float32 & operator[](x::uint64 i) { return x::vector<x::float32>::operator[](i); }
        public:     vector & operator-=(const vector & o);
        public:     vector & operator+=(const vector & o);
        public:     vector & operator*=(const x::float32 & v);
        public:     vector & operator<<(const vector & o);
        public:     vector & operator=(const x::initializer<x::float32> & list);
        public:     vector & operator=(const vector & o);
        public:     vector & operator=(vector && o) noexcept;
        public:     vector(const x::reference<x::array<x::float32> > reference, x::uint64 offset, x::uint64 length);
        public:     vector(x::array<x::float32> && o);
        public:     vector(x::float32 x, x::float32 y, x::float32 z);
        protected:  vector(x::float32 x, x::float32 y, x::float32 z, x::float32 w);
        public:     vector(const x::initializer<x::float32> & list);
        protected:  vector(const x::initializer<x::float32> & list, x::float32 w);
        public:     vector();
        public:     vector(const vector & o);
        public:     vector(vector && o) noexcept;
        public:     ~vector() override;
        public:     friend vector operator*(const vector & x, const x::float32 & y)
                    {
                        vector result = x;
                        result *= y;
                        return result;
                    }
        public:     friend vector operator*(const x::float32 & x, const vector & y)
                    {
                        vector result = y;
                        result *= x;
                        return result;
                    }
        public:     friend vector operator+(const vector & x, const vector & y)
                    {
                        assertion(x.__length != y.__length || x.__length == 0);

                        vector result = x;
                        result += y;
                        return result;
                    }
        public:     friend vector operator-(const vector & x, const vector & y)
                    {
                        assertion(x.__length != y.__length || x.__length == 0);

                        vector result = x;
                        result -= y;
                        return result;
                    }
        public:     friend bool operator!=(const vector & x, const vector & y)
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
        public:     friend bool operator==(const vector & x, const vector & y)
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
        public:     friend x::output::stream & operator<<(x::output::stream & os, const vector & o)
                    {
                        if(o.__reference.exist())
                        {
                            os << "[";
                            for(x::uint64 i = 0; i < o.__length; i++)
                            {
                                os << o[i] << ((i + 1 == o.__length) ? "" : ",");
                            }
                            os << "]";
                        }
                        else
                        {
                            os << "null";
                        }
                        return os;
                    }
        };
    }
}

#endif // __X_GRAPHICS__VECTOR__HH__
