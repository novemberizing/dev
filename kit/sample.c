#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <x/std.h>

struct queue;
struct integer;

typedef struct queue queue;
typedef struct integer integer;

struct queue
{
    integer * head;
    integer * tail;
    xuint64 size;
};

struct integer
{
    integer * prev;
    integer * next;
    int value;
};

extern integer * integernew(int value)
{
    printf("called\n");
    integer * o = (integer *) calloc(sizeof(integer), 1);
    o->value = value;
    return o;
}


#define xqueuepush(collection, type, item) do {     \
    type * real = item;                             \
    real->prev = collection->tail;                  \
    if(real->prev) {                                \
        real->prev->next = real;                    \
    } else {                                        \
        collection->head = real;                    \
    }                                               \
    collection->tail = real;                        \
    collection->size = collection->size + 1;        \
} while(0)

#define xqueuepop(collection, type, callback) do {  \
    if(collection->head) {                          \
        type * item = collection->head;             \
        collection->head = item->next;              \
        if(collection->head) {                      \
            collection->head->prev = xnil;          \
        } else {                                    \
            collection->tail = xnil;                \
        }                                           \
        collection->size = collection->size - 1;    \
        item->next = xnil;                          \
        callback(item);                             \
    }                                               \
} while(0)

#define xqueueempty(collection) (collection->size == 0)

static inline void integer_item_cb(integer * item) 
{
    printf("%d\n", item->value);
    free(item);
}

int main(int argc, char ** argv)
{
    srandom(time(xnil));
    queue q = { 0, };
    for(int i = 0; i < (int) random() % 64; i++) {
        printf("count: %d\n", i);
        xqueuepush(xaddressof(q), integer , integernew((int) random()));
    }
    
    while(xqueueempty(xaddressof(q)) == xfalse) {
        xqueuepop(xaddressof(q), integer, integer_item_cb);
    }

    
    return 0;
}