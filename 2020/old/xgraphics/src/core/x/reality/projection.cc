#include "projection.hh"

namespace x
{
    namespace reality
    {
        x::reality::projection x::reality::projection::__main(800.0f / 600.0f);
        x::reality::projection * x::reality::projection::__current = nullptr;

        projection::projection(x::real aspect)
        :   __fovy(45.0f),
            __aspect(aspect),
            __near(0.1f),
            __far(1000.0f),
            __matrix()
        {
            __matrix = x::reality::matrix::perspective(x::radian(__fovy), __aspect, __near, __far);
        }

        projection::projection()
        :   __fovy(45.0f),
            __aspect(1.0f),
            __near(0.1f),
            __far(1000.0f),
            __matrix()
        {
            __matrix = x::reality::matrix::perspective(x::radian(__fovy), __aspect, __near, __far);
        }

        projection::projection(const x::reality::projection & o)
        :   __fovy(o.__fovy),
            __aspect(o.__aspect),
            __near(o.__near),
            __far(o.__far),
            __matrix(o.__matrix)
        {
        }

        projection::projection(x::reality::projection && o) noexcept
        :   __fovy(o.__fovy),
            __aspect(o.__aspect),
            __near(o.__near),
            __far(o.__far),
            __matrix(o.__matrix)
        {
            o.__fovy = 45.0f;
            o.__aspect = 1.0f;
            o.__near = 0.1f;
            o.__far = 1000.0f;
            o.__matrix = x::reality::matrix::perspective(x::radian(o.__fovy), o.__aspect, o.__near, o.__far);
        }

        projection::~projection()
        {
            __fovy = 45.0f;
            __aspect = 1.0f;
            __near = 0.1f;
            __far = 1000.0f;
        }

        x::reality::projection & projection::operator=(const x::reality::projection & o)
        {
            if(&o != this)
            {
                __fovy = o.__fovy;
                __aspect = o.__aspect;
                __near = o.__near;
                __far = o.__far;
                __matrix = o.__matrix;
            }
            return *this;
        }

        x::reality::projection & projection::operator=(x::reality::projection && o) noexcept
        {
            if(&o != this)
            {
                __fovy = o.__fovy;
                __aspect = o.__aspect;
                __near = o.__near;
                __far = o.__far;
                __matrix = o.__matrix;

                o.__fovy = 45.0f;
                o.__aspect = 1.0f;
                o.__near = 0.1f;
                o.__far = 1000.0f;
                o.__matrix = x::reality::matrix::perspective(x::radian(o.__fovy), o.__aspect, o.__near, o.__far);
            }
            return *this;
        }
    }
}
