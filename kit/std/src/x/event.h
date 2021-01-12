#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xeventobj;
struct xeventgenerator;
struct xeventengine;

typedef struct xevent xevent;
typedef struct xeventobj xeventobj;
typedef struct xeventgenerator xeventgenerator;
typedef struct xeventengine xeventengine;

#define xevent_typemask_category    0xFF000000U
#define xevent_typemask_realtype    0x0000FFFFU

#define xevent_category_custom      0x01000000U
#define xevent_category_io          0x02000000U
#define xevent_category_time        0x03000000U
#define xevent_category_signal      0x04000000U

/**
 * @struct  xevent
 * @brief   이벤트 객체
 * @details ## 이벤트 타입 구조
 * 
 *          | 1              | 2 | 3 - 4           |
 *          | -------------- | - | --------------- |
 *          | event category | - | real event type |
 *  
 */
struct xevent
{
    xuint32 type;
    xeventobj * target;
    xeventgenerator * generator;
};

extern xevent * xeventnew(xuint32 type, xeventobj * target, xeventgenerator * generator);
extern void * xeventrem(void * p);

/**
 * @struct  xeventobj
 * @brief   이벤트 타겟 객체
 * @details 주석의 설명이 별로 마음에 들지 않는다.
 * 
 * 
 */
struct xeventobj
{

};

struct xeventobj_io
{
};

struct xeventobj_time
{

};

struct xeventobj_signal
{

};


#define xeventengine_status_void    0x00000000U
#define xeventengine_status_cancel  0x80000000U
#define xeventengine_status_on      0x00000001U

// C 는 상속에서 벗어나야 한다.

struct xeventengine
{
    xuint32 status;
};

#define xeventengineinit()  (xeventengine) { 0 }

extern int xeventengine_run(xeventengine * engine);


#endif // __NOVEMBERIZING_X__EVENT__H__
