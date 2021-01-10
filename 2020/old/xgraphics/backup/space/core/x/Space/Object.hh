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
                protected:  xSpace::Object * __object;
                public:     void start() override;
                public:     void update() override;
                public:     virtual void set(xSpace::Object * o);
                public:     xSpace::Object::Camera & operator=(const xSpace::Object::Camera & o) = delete;
                public:     xSpace::Object::Camera & operator=(xSpace::Object::Camera && o) noexcept = delete;
                protected:  Camera();
                public:     Camera(const xSpace::Object::Camera & o) = delete;
                public:     Camera(xSpace::Object::Camera && o) noexcept = delete;
                public:     ~Camera() override;
                };
    protected:  x::graphics::object * __object;
    protected:  x::physics::object * __physics;
    protected:  x::string __relationship;
    protected:  x::boolean __selected;
    public:     inline const x::string & relationship() const { return __relationship; }
    public:     void start(const x::reality::matrix & model, const x::reality::camera & camera) override;
    public:     void update(const x::reality::matrix & model, const x::reality::camera & camera) override;
    public:     void render(const x::reality::vector & eye) override { __object->render(eye); }
    public:     void selected(x::boolean v) override;
    public:     x::boolean selected() override { return __selected; }
    public:     const x::string & name() const override { return __object->name(); }
    public:     const x::reality::vector & position() const override { return __object->position(); }
    public:     const x::reality::vector & front() const override { return __object->front(); }
    public:     const x::reality::vector & up() const override { return __object->up(); }
    public:     const x::reality::vector & location() const override { return __object->location(); }
    public:     const x::reality::vector & rotation() const override { return __object->rotation(); }
    public:     const x::reality::vector & scale() const override { return __object->scale(); }
    public:     const x::reality::vector & axis() const override { return __object->axis(); }
    public:     const x::reality::matrix & model() const override { return __object->model(); }
    public:     x::uint64 level() const override { return __object->level(); }
    public:     x::graphics::program * program() override { return __object->program(); }
    public:     x::graphics::reference * reference() override { return __object->reference(); }
    public:     x::graphics::texture * texture() override { return __object->texture(); }
    public:     x::boolean bind(const x::string & name, x::uint32 id) override { return __object->bind(name, id); }

    public:     x::real velocity() const override { return __physics->velocity(); }
    public:     x::real force() const override { return __physics->force(); }
    public:     void force(x::real v) override { __physics->force(v); }
    public:     x::real energy() const override { return __physics->energy(); }
    public:     xSpace::Object & operator=(const xSpace::Object & o) = delete;
    public:     xSpace::Object & operator=(xSpace::Object && o) noexcept = delete;
    public:     Object(x::graphics::object * object, const x::string & relationship);
    public:     Object() = delete;
    public:     Object(const xSpace::Object & o) = delete;
    public:     Object(xSpace::Object && o) noexcept = delete;
    public:     ~Object() override;
    };
}

#endif // __X_SPACE__OBJECT__HH__
