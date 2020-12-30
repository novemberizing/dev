#ifndef   __X__NODE__HH__
#define   __X__NODE__HH__

namespace x
{
    class node
    {
    public:     node & operator=(const node & o)
                {
                    return *this;
                }
    public:     node & operator=(node && o) noexcept
                {
                    return *this;
                }
    public:     node()
                {
                }
    public:     node(const node & o)
                {
                }
    public:     node(node && o) noexcept
                {
                }
    public:     virtual ~node()
                {
                }
    };
}

#endif // __X__NODE__HH__
