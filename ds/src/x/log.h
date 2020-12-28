#ifndef   __NOVEMBERIZING_X__LOG__H__
#define   __NOVEMBERIZING_X__LOG__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define functionLog(format, ...)    fprintf(stdout, "[flow] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define criticalLog(format, ...)    fprintf(stdout, "[critical] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define errorLog(format, ...)       fprintf(stdout, "[error] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define warningLog(format, ...)     fprintf(stdout, "[warning] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define cautionLog(format, ...)     fprintf(stdout, "[caution] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define noticeLog(format, ...)      fprintf(stdout, "[notice] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define informationLog(format, ...) fprintf(stdout, "[information] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define debugLog(format, ...)       fprintf(stdout, "[debug] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__)
#define assertion(x, format, ...)   do {                                                                                    \
    if(x) {                                                                                                                 \
        fprintf(stdout, "[assert] %s/%ld " __FILE__ ":%d " format "\n", __func__, pthread_self(), __LINE__, ##__VA_ARGS__); \
        abort();                                                                                                            \
    }                                                                                                                       \
} while(0)

#endif // __NOVEMBERIZING_X__LOG__H__
