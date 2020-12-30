#include <x/array.hh>
#include <iostream>

int main()
{
    int source[5] = { 0, 1, 2, 3, 4 };
    x::array<int> o(source, 3);
    o.each([](const int & v){
        std::cout << v << std::endl;
    });
    return 0;
}
