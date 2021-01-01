/**
 * @file    x/log.h
 * @brief
 * @details 
 * 
 * @author  novemberizing <novemberizing@gmail.com>
 * 
 */
#ifndef   __NOVEMBERIZING_X__LOG__H__
#define   __NOVEMBERIZING_X__LOG__H__

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

extern FILE * xlogfobj(void);
extern void xlogfobjset(FILE * fp);

extern void xabort(void);
extern void xabortset(int status);

#define xfunction(format, ...)      fprintf(xlogfobj(), "[function] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)
#define xcritical(format, ...)      fprintf(xlogfobj(), "[critical] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)
#define xerror(format, ...)         fprintf(xlogfobj(), "[error] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)
#define xwarning(format, ...)       fprintf(xlogfobj(), "[warning] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)
#define xcaution(format, ...)       fprintf(xlogfobj(), "[caution] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)
#define xnotice(format, ...)        fprintf(xlogfobj(), "[notice] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)
#define xinformation(format, ...)   fprintf(xlogfobj(), "[information] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)
#define xdebug(format, ...)         fprintf(xlogfobj(), "[debug] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)
#define xverbose(format, ...)       fprintf(xlogfobj(), "[verbose] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__)

/**
 * @def     xassertion(condition, format, ...)
 * @brief
 * @details
 * 
 * @param   condition
 * @param   format
 * @param   ...
 */
#define xassertion(condition, format, ...) do {                                                                                         \
    if(condition) {                                                                                                                     \
        fprintf(xlogfobj(), "[assertion] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__);   \
        xabort();                                                                                                                       \
    }                                                                                                                                   \
} while(0)

/**
 * @def     xcheck(condition, ret, format, ...)
 * @brief
 * @details
 * 
 * @param   condition
 * @param   ret
 * @param   format
 * @param   ...
 * 
 */
#define xcheck(condition, ret, format, ...) do {                                                                                        \
    if(condition) {                                                                                                                     \
        fprintf(xlogfobj(), "[check] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__);       \
        return ret;                                                                                                                     \
    }                                                                                                                                   \
} while(0)

/**
 * @def     xcheckvoid(condition, ret, format, ...)
 * @brief
 * @details
 * 
 * @param   condition
 * @param   format
 * @param   ...
 * 
 */
#define xcheckvoid(condition, format, ...) do {                                                                                         \
    if(condition) {                                                                                                                     \
        fprintf(xlogfobj(), "[check] %s:%d %s:%lu => " format "\n", __FILE__, __LINE__, __func__, pthread_self(), ##__VA_ARGS__);       \
        return;                                                                                                                         \
    }                                                                                                                                   \
} while(0)

#endif // __NOVEMBERIZING_X__LOG__H__
