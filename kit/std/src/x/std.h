#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;
typedef unsigned char       xbyte;

#define xsuccess        0
#define xfail           -1
#define xnil            (void *)(0)
#define xinvalid        -1
#define xfalse          0
#define xtrue           1

extern int xlogfd(void);

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

#define xobj_mask_allocated     0x80000000U
#define xobj_mask_types         0x0000FFFFU

/** DATA STRUCTURE */

#define xqueuepush(queue, item) do {    \
    if(queue->tail) {                   \
        queue->tail->next = item;       \
        item->prev = queue->tail;       \
        queue->tail = item;             \
    } else {                            \
        queue->head = item;             \
        queue->tail = item;             \
    }                                   \
    queue->size = queue->size + 1;      \
} while(0)

#define xqueuepop(queue) queue->head, ( \
    queue->head ? (queue->head = queue->head->next, queue->size = queue->size - 1) : xnil, \
    queue->head ? (queue->head->prev = xnil, queue->tail = xnil) : xnil)

#define xqueuesize(queue)   queue->size
#define xqueueempty(queue)  queue ? queue->size == 0 : xtrue

/** BUFFER */

#define xobj_type_buffer        0x0000FFFFU

struct xbuffer;

typedef struct xbuffer xbuffer;

struct xbuffer
{
    xuint32 flags;

    xbyte * data;
    xuint64 position;
    xuint64 size;
    xuint64 capacity;
};

extern xbuffer * xbuffernew(xuint64 capacity);
extern void * xbufferrem(void * p);

#define xbufferfront(buffer)    (buffer->data + buffer->position)

/**
 * @def     xbufferback(buffer)
 * @brief   버퍼 객체의 내부 데이터 주소 값 (사용하지 않은 버퍼의 주소)
 * @details
 * 
 * @param   | buffer | in | xbuffer * | 버퍼 객체 |
 */
#define xbufferback(buffer)     (buffer->data + buffer->size)

/**
 * @def     xbufferremain(buffer)
 * @brief   버퍼 객체의 남은 크기
 * @details
 * 
 * @param   | buffer | in | xbuffer * | 버퍼 객체 |
 */
#define xbufferremain(buffer)   (buffer->capacity - buffer->size)

/** THREAD ********************************************/

extern unsigned long xthreadid(void);

#endif // __NOVEMBERIZING_X__STD__H__
