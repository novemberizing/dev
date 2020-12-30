#include <x/array.hh>

int main()
{
    x::array<int> source = { 1, 2, 3, 4, 5 };
    x::array<int> o = source;
    x::array<int> second(source);
    return 0;
}
