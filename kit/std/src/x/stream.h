#ifndef   __NOVEMBERIZING_X__STREAM__H__
#define   __NOVEMBERIZING_X__STREAM__H__

#include <x/std.h>

#define xstreamtype_buffer          (1)                     /**!< 바이트 버퍼 스트림 타입 */

#define xstreamtype_default         xstreamtype_buffer      /**!< 디폴트 스트림 타입: 바이트 버퍼 스트림 */

struct xstream;

typedef struct xstream xstream;                             /**!< 스트림 타입 */

typedef xstream * (*xstreamdestructor)(xstream *);          /**!< 스트림 소멸자 */

/**
 * @struct      xstream
 * @brief       스트림 인터페이스 구조체
 */
struct xstream
{
    xuint32 type;               /**!< 스트림 객체 타입 */
    xstreamdestructor rem;      /**!< 스트림 객체의 소멸자 */
};

extern xstream * xstreamnew(xuint32 type);
extern xstream * xstreamrem(xstream * o);

extern xbyte * xstreamback(xstream * o);
extern xbyte * xstreamfront(xstream * o);
extern xuint64 xstreamremain(xstream * o);
extern xuint64 xstreamlen(xstream * o);

extern xuint64 xstreamadjust(xstream * o, xint32 force);

extern xuint64 xstreamcapacity_set(xstream * o, xuint64 v);
extern xuint64 xstreamcapacity_get(xstream * o);
extern xuint64 xstreamsize_set(xstream * o, xuint64 n);
extern xuint64 xstreamsize_get(xstream * o);
extern xuint64 xstreampos_set(xstream * o, xuint64 n);
extern xuint64 xstreampos_get(xstream * o);


#endif // __NOVEMBERIZING_X__STREAM__H__
