#include "object.h"

extern xeventgenerator_node * xeventobject_register_generator_node(xeventobject * object, xeventgenerator_node * node)
{
    node->generatornode.prev = object->generators.tail;
    if(node->generatornode.prev)
    {
        node->generatornode.prev->generatornode.next = node;
    }
    else
    {
        object->generators.head = node;
    }
    object->generators.tail = node;
    object->generators.size = object->generators.size + 1;

    return node;
}

extern xeventgenerator_node * xeventobject_unregister_generator_node(xeventgenerator_node * node)
{
    xeventobject * object = node->generatornode.cntr;
    xeventgenerator_node * prev = node->generatornode.prev;
    xeventgenerator_node * next = node->generatornode.next;

    if(prev)
    {
        prev->generatornode.next = next;
    }
    else
    {
        object->generators.head = next;
    }

    if(next)
    {
        next->generatornode.prev = prev;
    }
    else
    {
        object->generators.tail = prev;
    }

    object->generators.size = object->generators.size - 1;

    return node;
}
