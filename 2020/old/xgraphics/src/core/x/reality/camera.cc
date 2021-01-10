#include "camera.hh"

namespace x
{
    namespace reality
    {
        x::reality::camera x::reality::camera::__main({0.0f, 0.0f, 500.0f, 1.0f});
        x::reality::camera * x::reality::camera::__current = nullptr;

        const x::reality::vector & camera::eye()
        {
            return __current != nullptr ? __current->location() : __main.location();
        }

        x::reality::camera & camera::current()
        {
            return __current != nullptr ? *__current : __main;
        }

        camera::camera(const x::reality::vector & location)
        :   __center({0.0f, 0.0f, 0.0f}),
            __up({0.0f, 1.0f, 0.0f}),
            __location(location),
            __matrix()
        {
        }

        camera::camera(const x::reality::vector & location, const x::reality::vector & center)
        :   __center(center),
            __up({0.0f, 1.0f, 0.0f}),
            __location(location),
            __matrix()
        {
        }

        camera::camera(const x::reality::vector & location, const x::reality::vector & center, const x::reality::vector & up)
        :   __center(center),
            __up(up),
            __location(location),
            __matrix()
        {
        }

        camera::camera()
        :   __center({0.0f, 0.0f, 0.0f}),
            __up({0.0f, 1.0f, 0.0f}),
            __location({0.0f, 0.0f, 100.0f}),
            __matrix()
        {
        }

        camera::camera(const x::reality::camera & o)
        :   __center(o.__center),
            __up(o.__up),
            __location(o.__location),
            __matrix(o.__matrix)
        {
        }

        camera::camera(x::reality::camera && o) noexcept
        :   __center(x::move(o.__center)),
            __up(x::move(o.__up)),
            __location(x::move(o.__location)),
            __matrix(x::move(o.__matrix))
        {
        }

        camera::~camera()
        {
        }

        x::reality::camera & camera::operator=(const x::reality::camera & o)
        {
            if(&o != this)
            {
                __center = o.__center;
                __up = o.__up;
                __location = o.__location;
                __matrix = o.__matrix;
            }
            return *this;
        }

        x::reality::camera & camera::operator=(x::reality::camera && o) noexcept
        {
            if(&o != this)
            {
                __center = x::move(o.__center);
                __up = x::move(o.__up);
                __location = x::move(o.__location);
                __matrix = x::move(o.__matrix);
            }
            return *this;
        }

        void camera::start()
        {
            __matrix = x::reality::matrix::lookat(__location, __center, __up);
        }

        void camera::update()
        {
            __matrix = x::reality::matrix::lookat(__location, __center, __up);
        }
    }
}
