#include "generator.h"

extern xeventgenerator_node * xeventgenerator_register_object(xeventgenerator * generator, xeventobject * object)
{
    xeventgenerator_node * node = calloc(sizeof(xeventgenerator_node), 1);

    node->generatornode.cntr = object;

    node->objectnode.cntr = generator;
    node->objectnode.prev = generator->tail;
    if(node->objectnode.prev)
    {
        node->objectnode.prev->objectnode.next = node;
    }
    else
    {
        generator->head = node;
    }
    generator->tail = node;
    generator->size = generator->size + 1;

    return xeventobject_register_generator_node(object, node);
}

extern void xeventgenerator_unregister_object(xeventgenerator_node * node)
{
    node = xeventobject_unregister_generator_node(node);

    xeventgenerator * generator = node->objectnode.cntr;
    xeventgenerator_node * prev = node->objectnode.prev;
    xeventgenerator_node * next = node->objectnode.next;

    if(prev)
    {
        prev->objectnode.next = next;
    }
    else
    {
        generator->head = next;
    }

    if(next)
    {
        next->objectnode.prev = prev;
    }
    else
    {
        generator->tail = prev;
    }
    generator->size = generator->size - 1;

    free(node);
}