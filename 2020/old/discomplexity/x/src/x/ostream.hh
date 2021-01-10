#ifndef   __X__OSTREAM__HH__
#define   __X__OSTREAM__HH__

namespace x
{
    class ostream
    {
    public:     typedef ostream & (*func)(ostream &);
    public:     virtual void write(char v)
                {
                }
    public:     virtual void write(signed char v)
                {
                }
    public:     virtual void write(unsigned char v)
                {
                }
    public:     virtual void write(short v)
                {
                }
    public:     virtual void write(unsigned short v)
                {
                }
    public:     virtual void write(int v)
                {
                }
    public:     virtual void write(unsigned int v)
                {
                }
    public:     virtual void write(long v)
                {
                }
    public:     virtual void write(unsigned long v)
                {
                }
    public:     virtual void write(long long v)
                {
                }
    public:     virtual void write(unsigned long long v)
                {
                }
    public:     virtual void write(float v)
                {
                }
    public:     virtual void write(double v)
                {
                }
    public:     virtual void write(long double v)
                {
                }
    public:     virtual void write(const char * v)
                {
                }
    public:     virtual void write(func f)
                {
                }
    public:     ostream & operator<<(func f)
                {
                    write(f);
                    return *this;
                }
    public:     ostream & operator<<(char v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(signed char v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(unsigned char v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(short v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(unsigned short v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(int v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(unsigned int v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(long v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(unsigned long v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(long long v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(unsigned long long v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(float v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(double v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(long double v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator<<(const char * v)
                {
                    write(v);
                    return *this;
                }
    public:     ostream & operator=(const ostream & o)
                {
                    return *this;
                }
    public:     ostream & operator=(ostream && o) noexcept
                {
                    return *this;
                }
    public:     ostream()
                {

                }
    public:     ostream(const ostream & o)
                {

                }
    public:     ostream(ostream && o) noexcept
                {
                }
    public:     virtual ~ostream()
                {

                }
    };

    inline ostream & endl(ostream & os)
    {
        os.write('\n');
        return os;
    }
}

#endif // __X__OSTREAM__HH__
