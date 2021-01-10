#ifndef   __X__LIST__HH__
#define   __X__LIST__HH__

#include <x/output/stream.hh>
#include <x/collection.hh>
#include <x/node.hh>

namespace x
{
    template <typename T>
    class list : public collection<T>
    {
    protected:  class node : public x::node
                {
                protected:  T value_;
                protected:  node * previous_;
                protected:  node * next_;
                public:     const T & value() const { return this->value_; }
                public:     T & value() { return this->value_; }
                public:     node * previous() const { return this->previous_; }
                public:     node * next() const { return this->next_; }
                public:     void next(node * n){ this->next_  = n; }
                public:     void previous(node * n){ this->previous_ = n; }
                public:     node & operator=(const node & o) = delete;
                public:     node & operator=(node && o) noexcept = delete;
                public:     node(T && value) : value_(x::move(value)), previous_(nullptr), next_(nullptr)
                            {
                            }
                public:     node(T && value, node * previous) : value_(x::move(value)), previous_(previous), next_(nullptr)
                            {
                            }
                public:     node(const T & value) : value_(value), previous_(nullptr), next_(nullptr)
                            {
                            }
                public:     node(const T & value, node * previous) : value_(value), previous_(previous), next_(nullptr)
                            {
                            }
                public:     node() : value_(), previous_(nullptr), next_(nullptr)
                            {
                            }
                public:     node(const node & o) = delete;
                public:     node(node && o) noexcept = delete;
                public:     virtual ~node()
                            {
                                this->previous_ = nullptr;
                                this->next_ = nullptr;
                            }
                };
    protected:  node * head_;
    protected:  node * tail_;
    protected:  uint64 size_;
    public:     x::uint64 size() const override { return this->size_; }
    public:     x::boolean empty() const override { return this->size_ == 0 || this->head_ == nullptr || this->tail_ == nullptr; }
    public:     void each(std::function<void(const T&)> f) const override
                {
                    if (f)
                    {
                        for (typename list<T>::node* i = this->head_; i != nullptr; i = i->next())
                        {
                            f(i->value());
                        }
                    }
                }
    public:     void add(const T & item) override
                {
                    this->push(item);
                }
    public:     void add(T && item) override
                {
                    this->push(x::move(item));
                }
    public:     void clear() override
                {
                    this->clear(nullptr);
                }
    public:     void clear(std::function<void (T &&)> f) override
                {
                    for(typename list<T>::node * i = this->head_; i != nullptr; )
                    {
                        typename list<T>::node * n = i;
                        i = i->next();
                        if (f)
                        {
                            f(x::move(n->value()));
                        }
                        delete n;
                    }
                    this->head_ = nullptr;
                    this->tail_ = nullptr;
                    this->size_ = 0;
                }
    public:     virtual void push(const T & v)
                {
                    if(this->tail_ == nullptr)
                    {
                        this->tail_ = new typename list<T>::node(v);
                        this->head_ = this->tail_;
                    }
                    else
                    {
                        typename list<T>::node * n = new typename list<T>::node(v, this->tail_);
                        this->tail_->next(n);
                        this->tail_ = n;
                    }
                    this->size_++;
                }
    public:     virtual void push(T && v)
                {
                    if(this->tail_ == nullptr)
                    {
                        this->tail_ = new typename list<T>::node(x::move(v));
                        this->head_ = this->tail_;
                    }
                    else
                    {
                        typename list<T>::node * n = new typename list<T>::node(x::move(v), this->tail_);
                        this->tail_->next(n);
                        this->tail_ = n;
                    }
                    this->size_++;
                }
    public:     virtual bool pop(std::function<void (T && value)> f)
                {
                    if(this->empty())
                    {
                        return false;
                    }
                    else
                    {
                        typename list<T>::node * n = this->head_;
                        typename list<T>::node * next = this->head_->next();
                        if(next)
                        {
                            next->previous(nullptr);
                        }
                        this->head_ = next;
                        n->next(nullptr);
                        this->size_--;
                        if(this->size_ == 0)
                        {
                            this->head_ = nullptr;
                            this->tail_ = nullptr;
                        }
                        if(f)
                        {
                            f(x::move(n->value()));
                        }
                        delete n;
                        return true;
                    }
                }
    public:     virtual T pop()
                {
                    if(head_)
                    {
                        typename list<T>::node * n = this->head_;
                        typename list<T>::node * next = this->head_->next();
                        if(next)
                        {
                            next->previous(nullptr);
                        }
                        this->head_ = next;
                        n->next(nullptr);
                        this->size_--;
                        if(this->size_ == 0)
                        {
                            this->head_ = nullptr;
                            this->tail_ = nullptr;
                        }
                        T result = std::move(n->value());
                        delete n;
                        return result;
                    }
                    else
                    {
                        exceptional();
                    }
                }
    public:     list<T> & operator=(const std::initializer_list<T> & list)
                {
                    clear();
                    for(typename std::initializer_list<T>::iterator it = list.begin(); it != list.end(); ++it)
                    {
                        if(this->tail_ == nullptr)
                        {
                            this->tail_ = new typename x::list<T>::node(*it);
                            this->head_ = this->tail_;
                        }
                        else
                        {
                            typename x::list<T>::node * n = new typename x::list<T>::node(*it, this->tail_);
                            this->tail_->next(n);
                            this->tail_ = n;
                        }
                        this->size_++;
                    }
                    return *this;
                }
    public:     list<T> & operator=(const list<T> & o)
                {
                    if(&o != this)
                    {
                        clear();
                        for(typename list<T>::node * i = o.head_; i != nullptr; i = i->next())
                        {
                            if(this->tail_ == nullptr)
                            {
                                this->tail_ = new typename list<T>::node(i->value());
                                this->head_ = this->tail_;
                            }
                            else
                            {
                                typename list<T>::node * n = new typename list<T>::node(i->value(), this->tail_);
                                this->tail_->next(n);
                                this->tail_ = n;
                            }
                            this->size_++;
                        }
                    }
                    return *this;
                }
    public:     list<T> & operator=(list<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        clear();
                        this->head_ = o.head_;
                        this->tail_ = o.tail_;
                        this->size_ = o.size_;

                        o.head_ = nullptr;
                        o.tail_ = nullptr;
                        o.size_ = 0;
                    }
                    return *this;
                }
    public:     list(const std::initializer_list<T> & list) : head_(nullptr), tail_(nullptr), size_(0)
                {
                    for(typename std::initializer_list<T>::iterator it = list.begin(); it != list.end(); ++it)
                    {
                        if(this->tail_ == nullptr)
                        {
                            this->tail_ = new typename x::list<T>::node(*it);
                            this->head_ = this->tail_;
                        }
                        else
                        {
                            typename x::list<T>::node * n = new typename x::list<T>::node(*it, this->tail_);
                            this->tail_->next(n);
                            this->tail_ = n;
                        }
                        this->size_++;
                    }
                }
    public:     list() : head_(nullptr), tail_(nullptr), size_(0)
                {
                }
    public:     list(const list<T> & o) : head_(nullptr), tail_(nullptr), size_(0)
                {
                    for(typename list<T>::node * i = o.head_; i != nullptr; i = i->next())
                    {
                        if(this->tail_ == nullptr)
                        {
                            this->tail_ = new typename list<T>::node(i->value());
                            this->head_ = this->tail_;
                        }
                        else
                        {
                            typename list<T>::node * n = new typename list<T>::node(i->value(), this->tail_);
                            this->tail_->next(n);
                            this->tail_ = n;
                        }
                        this->size_++;
                    }
                }
    public:     list(list<T> && o) noexcept : head_(o.head_), tail_(o.tail_), size_(o.size_)
                {
                    o.head_ = nullptr;
                    o.tail_ = nullptr;
                    o.size_ = 0;
                }
    public:     ~list() override
                {
                    for(typename list<T>::node * i = this->head_; i != nullptr; )
                    {
                        typename list<T>::node * n = i;
                        i = i->next();
                        delete n;
                    }
                    this->head_ = nullptr;
                    this->tail_ = nullptr;
                    this->size_ = 0;
                }
    public:     friend x::output::stream & operator<<(x::output::stream & os, const list<T> & o)
                {
                    if(o.size_ == 0 || o.head_ == nullptr || o.tail_ == nullptr)
                    {
                        os << "null";
                    }
                    else
                    {
                        os << "[";
                        for(typename list<T>::node * i = o.head_; i != nullptr; i = i->next())
                        {
                            os << i->value();
                            if(i->next() != nullptr)
                            {
                                os << ",";
                            }
                        }
                        os << "]";
                    }
                    return os;
                }
    };
}

#endif // __X__LIST__HH__
