#ifndef   __X_GRAPHICS_OBJECTS__TRIANGLE__HH__
#define   __X_GRAPHICS_OBJECTS__TRIANGLE__HH__

// #include <x/graphics/primitive.hh>
//
// namespace x
// {
//     namespace Graphics
//     {
//         namespace Objects
//         {
//             class Triangle : public Primitive
//             {
//             public:     Triangle & operator=(const Triangle & o)
//                         {
//                             if(&o != this)
//                             {
//                                 Primitive::operator=(o);
//                             }
//                             return *this;
//                         }
//             public:     Triangle & operator=(Triangle && o) noexcept
//                         {
//                             if(&o != this)
//                             {
//                                 Primitive::operator=(x::move(o));
//                             }
//                             return *this;
//                         }
//             public:     Triangle()
//                         :   Primitive()
//                         {
//                             __buffer.target(Buffer::ARRAY);
//                             __buffer.usage(Buffer::STATIC, Buffer::DRAW);
//
//                             __vertices.mode(Vertices::TRIANGLE);
//                             __vertices.push(Vertex({  0.0f,  1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }));
//                             __vertices.push(Vertex({ -1.0f, -1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }));
//                             __vertices.push(Vertex({  1.0f, -1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }));
//                         }
//             public:     Triangle(const Triangle & o)
//                         :   Primitive(o)
//                         {
//                         }
//             public:     Triangle(Triangle && o) noexcept
//                         :   Primitive(x::move(o))
//                         {
//
//                         }
//             public:     ~Triangle() override
//                         {
//                         }
//             };
//         }
//     }
// }

#endif // __X_GRAPHICS_OBJECTS__TRIANGLE__HH__
