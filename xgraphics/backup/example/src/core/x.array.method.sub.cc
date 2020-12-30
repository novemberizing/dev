#include <x/array.hh>
#include <iostream>

int main()
{
    x::array<int> o;
    for(x::uint64 i = 0; i < 128; i++)
    {
        o.push(i);
    }
    x::array<int> destination = o.sub(16, 8);
    destination.each([](const int & v){
        std::cout << v << std::endl;
    });
}
