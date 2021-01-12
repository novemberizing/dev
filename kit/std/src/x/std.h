#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

#define xsuccess        0
#define xfail           -1
#define xnil            (void *)(0)
#define xinvalid        -1
#define xfalse          0
#define xtrue           1

#define xassertion(condition, format, ...) do {     \
    if(condition) {                                 \
        dprintf(xlogfd(), "[assertion] %s:%d "      \
                          "%s:%lu => "              \
                          format "\n",              \
                          __FILE__, __LINE__,       \
                          __func__, xthreadid(),    \
                          ##__VA_ARGS__);           \
    }                                               \
} while(0)

#endif // __NOVEMBERIZING_X__STD__H__
