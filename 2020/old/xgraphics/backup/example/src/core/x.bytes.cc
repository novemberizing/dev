#include <x/bytes.hh>
#include <iostream>

int main()
{
    x::bytes o = { 1, 2, 3, 4, 5 };
    for(x::uint64 i = 0; i < o.size(); i++)
    {
        std::cout << (int) o[i] << std::endl;
    }
    return 0;
}
