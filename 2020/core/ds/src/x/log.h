#ifndef   __NOVEMBERIZING_X__LOG__H__
#define   __NOVEMBERIZING_X__LOG__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

extern void xlogfileset(FILE * f);
extern FILE * xlogfileget(void);

#define xfunction(format, ...)    fprintf(xlogfileget(), "[flow] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define xcritical(format, ...)    fprintf(xlogfileget(), "[critical] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define xerror(format, ...)       fprintf(xlogfileget(), "[error] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define xwarning(format, ...)     fprintf(xlogfileget(), "[warning] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define xcaution(format, ...)     fprintf(xlogfileget(), "[caution] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define xnotice(format, ...)      fprintf(xlogfileget(), "[notice] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define xinformation(format, ...) fprintf(xlogfileget(), "[information] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define xdebug(format, ...)       fprintf(xlogfileget(), "[debug] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define xassertion(x, format, ...)   do {                                                                                            \
    if(x) {                                                                                                                         \
        fprintf(xlogfileget(), "[assert] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__);  \
        abort();                                                                                                                    \
    }                                                                                                                               \
} while(0)

// return void case ...
#define xcheck(x, ret, format, ...)  do {                                                                                           \
    if(x) {                                                                                                                         \
        fprintf(xlogfileget(), "[assert] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__);  \
        abort();                                                                                                                    \
        return ret;                                                                                                                 \
    }                                                                                                                               \
} while(0)

extern int __check_x_log(int total);

#endif // __NOVEMBERIZING_X__LOG__H__
