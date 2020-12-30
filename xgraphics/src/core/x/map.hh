#ifndef   __X__MAP__HH__
#define   __X__MAP__HH__

#include <x/set.hh>
#include <x/pair.hh>

namespace x
{
    template <typename K, typename V, typename TUPLE = x::pair<K, V> >
    class map : public x::set<K, TUPLE>
    {
    public:     virtual void put(const K & key, const V & value)
                {
                    this->add(TUPLE(key, value));
                }
    public:     virtual void put(const K & key, V && value)
                {
                    this->add(TUPLE(key, x::move(value)));
                }
    public:     virtual x::boolean until(x::function<x::boolean (V&)> f)
                {
                    if(f)
                    {
                        typename x::map<K, V, TUPLE>::node * current = this->__root->minimum();
                        while(current)
                        {
                            if(f(current->item().second()))
                            {
                                return true;
                            }
                            current = current->next();
                        }
                    }
                    return false;
                }
    public:     virtual x::boolean until(x::function<x::boolean (const V&)> f) const
                {
                    if(f)
                    {
                        typename x::map<K, V, TUPLE>::node * current = this->__root->minimum();
                        while(current)
                        {
                            if(f(current->item().second()))
                            {
                                return true;
                            }
                            current = current->next();
                        }
                    }
                    return false;
                }
    public:     virtual void each(x::function<void (const K &, V &)> f)
                {
                    if(f)
                    {
                        typename x::map<K, V, TUPLE>::node * current = this->__root->minimum();
                        while(current)
                        {
                            f(current->key(), current->item().second());
                            current = current->next();
                        }
                    }
                }
    public:     virtual void each(x::function<void (const K &, const V &)> f) const
                {
                    if(f)
                    {
                        typename x::map<K, V, TUPLE>::node * current = this->__root->minimum();
                        while(current)
                        {
                            f(current->key(), current->item().second());
                            current = current->next();
                        }
                    }
                }
    public:     void each(x::function<void (const K &)> f) const override
                {
                    x::set<K, TUPLE>::each(f);
                }
    public:     void each(x::function<void (const TUPLE &)> f) const override
                {
                    x::set<K, TUPLE>::each(f);
                }
    protected:  void each(x::function<void (TUPLE &)> f) override
                {
                    x::set<K, TUPLE>::each(f);
                }
    public:     const V & operator[](const K & key) const
                {
                    typename x::map<K, V, TUPLE>::node * n = this->find(key);

                    assertion(n == nullptr);

                    return n->item().second();
                }
    public:     V & operator[](const K & key)
                {
                    typename x::map<K, V, TUPLE>::node * n = this->find(key);

                    assertion(n == nullptr);

                    return n->item().second();
                }
    public:     x::map<K, V, TUPLE> & operator=(const x::map<K, V, TUPLE> & o)
                {
                    if(&o != this)
                    {
                        x::set<K, TUPLE>::operator=(o);
                    }
                    return *this;
                }
    public:     x::map<K, V, TUPLE> & operator=(x::map<K, V, TUPLE> && o) noexcept
                {
                    if(&o != this)
                    {
                        x::set<K, TUPLE>::operator=(x::move(o));
                    }
                    return *this;
                }
    public:     map()
                : x::set<K, TUPLE>()
                {
                }
    public:     map(const x::map<K, V, TUPLE> & o)
                :   x::set<K, TUPLE>(o)
                {
                }
    public:     map(x::map<K, V, TUPLE> && o) noexcept
                :   x::set<K, TUPLE>(x::move(o))
                {
                }
    public:     ~map() override
                {
                }
    };
}

#endif // __X__MAP__HH__
