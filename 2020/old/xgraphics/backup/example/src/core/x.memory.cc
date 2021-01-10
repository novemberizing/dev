#include <x/core.hh>

class Helloworld
{
public:     Helloworld & operator=(const Helloworld & o){ return *this; }
public:     Helloworld & operator=(Helloworld && o) noexcept { return *this; }
public:     Helloworld(){}
public:     Helloworld(const Helloworld & o){}
public:     Helloworld(Helloworld && o) noexcept {}
public:     virtual ~Helloworld(){}
};

int main()
{
    {
        void * p = x::memory::allocate<void>(16);
        assertion(p == nullptr);
        p = x::memory::allocate<void>(p, 32);
        assertion(p == nullptr);
        x::memory::deallocate<void>(p);
    }

    {
        Helloworld item;
        Helloworld * p = x::memory::allocate<Helloworld>(16);
        assertion(p == nullptr);
        x::memory::construct<Helloworld>(p, Helloworld());
        x::memory::destruct<Helloworld>(p, 1);
        x::memory::deallocate<Helloworld>(p);
    }

    return 0;
}
