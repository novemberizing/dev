#include <x/array.hh>
#include <iostream>

int main()
{
    x::array<int> o;
    for(x::uint64 i = 0; i < 128; i++)
    {
        o.push(i);
    }
    x::array<int> destination = { 1, 2, 3, 4, 5 };
    destination.each([](const int & v){
        std::cout << v << std::endl;
    });
}
