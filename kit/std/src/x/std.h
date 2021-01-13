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

/** HELPER */

#define xaddressof(o)   (&o)

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

/** THREAD */

#define xsynclock(sync)
#define xsyncunlock(sync)

/** DATA STRUCTURE */

// GENERIC CONTAINR
#define xcontainerlock(container)   xsynclock(container->sync);
#define xcontainerunlock(container) xsyncunlock(container->sync);

// LIST

#define xlistfront(collection)  (collection->head)
#define xlistnext(item)         (item->next)
#define xlistempty(collection)  (collection->size == 0)
#define xlistsize(collection)   (collection->size)

#define xlistpushback(collection, type, item) do {      \
    type * real = item;                                 \
    real->prev = collection->tail;                      \
    if(real->prev) {                                    \
        real->prev->next = real;                        \
    } else {                                            \
        collection->head = real;                        \
    }                                                   \
    collection->tail = real;                            \
    collection->size = collection->size + 1;            \
} while(0)

#define xlistpopfront(collection, type, callback) do {  \
    if(collection->head) {                              \
        type * item = collection->head;                 \
        collection->head = item->next;                  \
        if(collection->head) {                          \
            collection->head->prev = xnil;              \
        } else {                                        \
            collection->tail = xnil;                    \
        }                                               \
        collection->size = collection->size - 1;        \
        item->next = xnil;                              \
        if(callback) {                                  \
            callback(item);                             \
        }                                               \
    }                                                   \
} while(0)

#define xlisteach(collection, type, func) do {          \
    for(type * item = xlistfront(collection);           \
        item != xnil;                                   \
        item = xlistnext(item)) {                       \
        func(item);                                     \
    }                                                   \
} while(0);

// TODO: CHECK OUT SECTION

#define xqueuepush(collection, type, item)      xlistpushback(collection, type, item)
#define xqueuepop(collection, type, callback)   xlistpopfront(collection, type, callback)
#define xqueueempty(collection)                 xlistempty(collection)
#define xqueuesize(collection)                  xlistsize(collection)

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
