#ifndef   __X__MAP__HH__
#define   __X__MAP__HH__

#include <x/output/stream.hh>
#include <x/set.hh>
#include <x/pair.hh>

namespace x
{
    template <typename K, typename V, typename TUPLE = pair<K, V> >
    class map : public set<K, TUPLE>
    {
    public:     virtual void put(const K & key, const V & value)
                {
                    this->add(x::move(TUPLE(key, value)));
                }
    public:     virtual void put(const K & key, V && value)
                {
                    this->add(x::move(TUPLE(key, x::move(value))));
                }
    public:     virtual void each(std::function<void (const K &, V &)> f)
                {
                    if(f)
                    {
                        typename set<K, TUPLE>::node * current = this->__root->minimum();
                        while(current)
                        {
                            TUPLE & tuple = current->item();
                            f(tuple.first(), tuple.second());
                            current = current->next();
                        }
                    }
                }
    public:     void each(std::function<void (const TUPLE &)> f) const override
                {
                    set<K, TUPLE>::each(f);
                }
    public:     const V & operator[](const K & k) const
                {
                    const typename map<K, V, TUPLE>::node * n = this->find(k);
                    if(n == nullptr)
                    {
                        exceptional();
                    }
                    return n->item().second();
                }
    public:     V & operator[](const K & k)
                {
                    typename map<K, V, TUPLE>::node * n = this->find(k);
                    if(n == nullptr)
                    {
                        exceptional();
                    }
                    return n->item().second();
                }
    public:     map<K, V, TUPLE> & operator=(const map<K, V, TUPLE> & o)
                {
                    if(&o != this)
                    {
                        this->clear();
                        typename map<K, V, TUPLE>::node * current = o.__root->minimum();
                        while(current)
                        {
                            this->add(current->item());
                            current = current->next();
                        }
                    }
                    return *this;
                }
    public:     map<K, V, TUPLE> & operator=(map<K, V, TUPLE> && o) noexcept
                {
                    if(&o != this)
                    {
                        this->__root = o.__root;
                        this->__size = o.__size;

                        o.__root = nullptr;
                        o.__size = 0L;
                    }
                    return *this;
                }
    public:     map(const std::initializer_list<K> & list) : set<K, TUPLE>(list)
                {
                }
    public:     map() : set<K, TUPLE>()
                {
                }
    public:     map(const map<K, V, TUPLE> & o) : set<K, TUPLE>(o)
                {
                }
    public:     map(map<K, V, TUPLE> && o) noexcept : set<K, TUPLE>(x::move(o))
                {
                }
    public:     ~map() override
                {
                }
    public:     friend x::output::stream & operator<<(x::output::stream & os, const map<K, V, TUPLE> & o)
                {
                    if(o.__root != nullptr && o.__size > 0)
                    {
                        os << "{";
                        typename map<K, V, TUPLE>::node * current = o.__root->minimum();
                        while(current)
                        {
                            os << current->key() << ": " << current->item().second();
                            current = current->next();
                            if(current)
                            {
                                os << ",";
                            }
                        }
                        os << "}";
                    }
                    else
                    {
                        os << "null";
                    }
                    return os;
                }
    };
}

#endif // __X__MAP__HH__
