#include "matrix.hh"

#include <x/console.hh>

int main()
{
    {
        x::matrix<x::float32> o;
    }
    {
        x::matrix<x::float32> o = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        x::console::out << o << x::endl;
        x::console::out << o.symmetric() << x::endl;
        x::console::out << o << x::endl;
        x::console::out << o.pow(2) << x::endl;
        x::console::out << o << x::endl;
        x::console::out << o.transpose() << x::endl;
        x::console::out << o << x::endl;
    }
    return 0;
}
