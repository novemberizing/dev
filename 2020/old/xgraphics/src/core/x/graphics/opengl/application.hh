#ifndef   __X_GRAPHICS_OPENGL__APPLICATION__HH__
#define   __X_GRAPHICS_OPENGL__APPLICATION__HH__

#include <x/graphics/opengl.hh>
#include <x/graphics/application.hh>

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            class application : public x::graphics::application
            {
            public:     static x::graphics::application & init(int argc, char ** argv, x::function<void (x::graphics::application &)> func);
            protected:  x::uint32 __mode;
            protected:  x::uint32 __major;
            protected:  x::uint32 __minor;
            public:     void load(x::graphics::shader & o) override;
            public:     void load(x::graphics::program & o) override;
            public:     void load(x::graphics::primitive & o) override;
            public:     void load(x::graphics::buffer & o) override;
            public:     void load(x::graphics::vertices & o) override;
            public:     void load(x::graphics::texture & o) override;
            public:     void unload(x::graphics::texture & o) override;
            public:     void unload(x::graphics::vertices & o) override;
            public:     void unload(x::graphics::buffer & o) override;
            public:     void unload(x::graphics::primitive & o) override;
            public:     void unload(x::graphics::program & o) override;
            public:     void unload(x::graphics::shader & o) override;
            public:     void bind(x::graphics::vertices & o) override;
            public:     void bind(x::graphics::buffer & o) override;
            public:     void bind(x::graphics::texture & o) override;
            public:     void bind(x::graphics::program & o, x::graphics::object & object) override;
            public:     void bind(x::uint32 id, const x::reality::vector & vector) override;
            public:     void bind(x::uint32 id, const x::reality::matrix & matrix) override;
            public:     void bind(x::uint32 id, const x::reality::color & color) override;
            public:     void bind(x::uint32 id, x::real v) override;
            public:     void bind(x::uint32 id, x::int32 v) override;
            public:     void bind(x::uint32 index, x::uint32 size, x::graphics::buffer & buffer, x::uint32 stride, x::uint64 position) override;
            public:     void draw(const x::graphics::vertices & vertices, const x::array<x::uint32> & indices) override;
            public:     void draw(const x::graphics::vertices & vertices) override;
            public:     x::int32 run() override;
            public:     void render() override;
            public:     void render(x::graphics::reference & reference) override;
            public:     void idle() override;
            public:     void animation() override;
            public:     x::graphics::opengl::application & operator=(const x::graphics::opengl::application & o) = delete;
            public:     x::graphics::opengl::application & operator=(x::graphics::opengl::application && o) noexcept = delete;
            public:     application();
            public:     application(const x::graphics::opengl::application & o) = delete;
            public:     application(x::graphics::opengl::application && o) noexcept = delete;
            public:     ~application();
            };
        }
    }
}

#endif // __X_GRAPHICS_OPENGL__APPLICATION__HH__
