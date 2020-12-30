#include <x/array.hh>

#include <iostream>

int main(int argc, char ** argv)
{
    x::array<int> o(1, 15);
    o.each([](const int & v){
        std::cout << v << std::endl;
    });
    return 0;
}
