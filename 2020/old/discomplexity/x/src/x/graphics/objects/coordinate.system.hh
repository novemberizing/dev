#ifndef   __X_GRAPHICS_OBJECTS__COORDINATE_SYSTEM__HH__
#define   __X_GRAPHICS_OBJECTS__COORDINATE_SYSTEM__HH__

// #include <x/graphics/primitive.hh>
// #include <x/graphics/opengl/shaders/standard.hh>
//
// namespace x
// {
//     namespace Graphics
//     {
//         namespace Objects
//         {
//             class CoordinateSystem : public Primitive
//             {
//             public:     void render() override
//                         {
//                             if(__status != 0)
//                             {
//                                 Application & application = Application::get();
//                                 Camera & camera = application.camera();
//                                 Light & light = application.light();
//                                 Program & program = this->program();
//
//                                 __matrix << (__model * camera.matrix() * application.projection());
//
//                                 application.bind(program);
//                                 application.bind(program["mvp"], __matrix);
//
//                                 application.bind(program);
//
//                                 application.render(*this);
//                             }
//                         }
//             public:     CoordinateSystem & operator=(const CoordinateSystem & o)
//                         {
//                             if(&o != this)
//                             {
//                                 Primitive::operator=(o);
//                             }
//                             return *this;
//                         }
//             public:     CoordinateSystem & operator=(CoordinateSystem && o) noexcept
//                         {
//                             if(&o != this)
//                             {
//                                 Primitive::operator=(x::move(o));
//                             }
//                             return *this;
//                         }
//             public:     CoordinateSystem()
//                         :   Primitive()
//                         {
//                             __status = 1;
//                             __buffer.target(Buffer::ARRAY);
//                             __buffer.usage(Buffer::STATIC, Buffer::DRAW);
//
//                             __vertices.mode(Vertices::LINE);
//                             __vertices.push(Vertex({ 100000.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}));
//                             __vertices.push(Vertex({ 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}));
//                             __vertices.push(Vertex({ 0.0f, 100000.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}));
//                             __vertices.push(Vertex({ 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}));
//                             __vertices.push(Vertex({ 0.0f, 0.0f, 100000.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f, 1.0f, 1.0f}));
//                             __vertices.push(Vertex({ 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f, 1.0f, 1.0f}));
//
//                             Program program;
//
//                             program.set("mvp");
//                             program.add(OpenGL::Shaders::Coordinate::VERTEX);
//                             program.add(OpenGL::Shaders::Coordinate::FRAGMENT);
//
//                             __program = program;
//                             // __basis = Matrix::identity();
//                             // __model = Matrix::identity();
//
//                             console::out << __status << endl;
//                         }
//             public:     CoordinateSystem(const CoordinateSystem & o)
//                         :   Primitive(o)
//                         {
//                         }
//             public:     CoordinateSystem(CoordinateSystem && o) noexcept
//                         :   Primitive(x::move(o))
//                         {
//
//                         }
//             public:     ~CoordinateSystem() override
//                         {
//                         }
//             };
//         }
//     }
// }

#endif // __X_GRAPHICS_OBJECTS__COORDINATE_SYSTEM__HH__
