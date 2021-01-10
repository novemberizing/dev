#ifndef   __X_SPACE_GAME__ME__HH__
#define   __X_SPACE_GAME__ME__HH__

#include <x/array.hh>

#include <x/Space/Object.hh>

namespace xSpace
{
    namespace Game
    {
        class Me
        {
        protected:  xSpace::Object * __main;
        protected:  xSpace::Object * __selected;
        protected:  x::array<xSpace::Object *> __group;
        protected:  x::uint64 __selection;
        public:     inline x::uint64 selection() const { return __selection; }
        public:     virtual xSpace::Object * select(x::uint64 n);
        public:     virtual void main(xSpace::Object * o);
        public:     xSpace::Game::Me & operator=(const xSpace::Game::Me & o) = delete;
        public:     xSpace::Game::Me & operator=(xSpace::Game::Me & o) noexcept = delete;
        public:     Me();
        public:     Me(const xSpace::Game::Me & o) = delete;
        public:     Me(xSpace::Game::Me && o) noexcept = delete;
        public:     virtual ~Me();
        };
    }
}

#endif // __X_SPACE_GAME__ME__HH__
