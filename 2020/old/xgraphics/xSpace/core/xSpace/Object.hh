#ifndef   __X_SPACE__OBJECT__HH__
#define   __X_SPACE__OBJECT__HH__

#include <x/graphics/object.hh>

namespace xSpace
{
    class Object : public x::graphics::object
    {
    public:     class Camera : public x::reality::camera
                {
                protected:  static xSpace::Object::Camera * __singleton;
                public:     static xSpace::Object::Camera & get();
                protected:  x::graphics::object * __object;
                public:     virtual void set(x::graphics::object * object);
                protected:  Camera();
                public:     ~Camera() override;
                public:     Camera(const xSpace::Object::Camera & o) = delete;
                public:     Camera(xSpace::Object::Camera && o) noexcept = delete;
                public:     xSpace::Object::Camera & operator=(const xSpace::Object::Camera & o) = delete;
                public:     xSpace::Object::Camera & operator=(xSpace::Object::Camera && o) noexcept = delete;
                };
    protected:  x::string __name;
    protected:  x::reality::vector __position;
    protected:  x::reality::vector __front;
    protected:  x::reality::vector __up;
    protected:  x::reality::matrix __model;
    protected:  x::graphics::object * __graphics;
    protected:  x::real __velocity;
    protected:  x::real __force;
    public:     const x::string & name() const override { return __name; }
    public:     const x::reality::vector & position() const override { return __position; }
    public:     const x::reality::vector & front() const override { return __front; }
    public:     const x::reality::vector & up() const override { return __up; }
    public:     x::real mass() const override { return __graphics->mass(); }
    public:     x::real velocity() const override { return __velocity; }
    public:     x::real force() const override { return __force; }
    public:     void start(const x::reality::matrix & model, const x::reality::vector & eye) override;
    public:     void update(const x::reality::matrix & model, const x::reality::vector & eye) override;
    public:     void render(const x::reality::vector & position, const x::reality::vector & center) override;
    public:     Object(const x::string & name, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up, x::graphics::object * graphics);
    public:     ~Object() override;
    public:     xSpace::Object & operator=(const xSpace::Object & o) = delete;
    public:     xSpace::Object & operator=(xSpace::Object && o) noexcept = delete;
    public:     Object() = delete;
    public:     Object(const xSpace::Object & o) = delete;
    public:     Object(xSpace::Object && o) noexcept = delete;
    };
}

#endif // __X_SPACE__OBJECT__HH__
