// #include <stdio.h>
// #include <stdlib.h>

// #include "event.h"

// /**
//  * @fn      xevent * xeventnew(xuint32 type, xeventobj * target, xeventgenerator * generator)
//  * @brief   이벤트를 생성합니다.
//  * @details 동적할당으로 생성해야 할까?
//  * 
//  * @param   type      | xuint32 | in | 이벤트 타입 |
//  * @param   target    | xeventobj * | in | 이벤트 타겟 |
//  * @param   generator | xeventgenerator * | in | 이벤트를 생성한 제네레이터 |
//  * 
//  * @return  | event * | 이벤트 객체 |
//  */
// xevent * xeventnew(xuint32 type, xeventobj * target, xeventgenerator * generator)
// {
//     xevent * o = (xevent *) malloc(sizeof(xevent));

//     o->type = type;
//     o->target = target;
//     o->generator = generator;

//     return o;
// }

// /**
//  * @fn      void * xeventrem(void * p)
//  * @brief   이벤트 객체를 메모리에서 해제합니다.
//  * @details
//  * 
//  * @param   p | void * | in | 이벤트 객체의 포인터 주소 |
//  * 
//  * @return  | void * | 해제된 이벤트 객체의 주소로 언제나 널을 리턴합니다. |
//  */
// void * xeventrem(void * p)
// {
//     xassertion(p == xnil, "null pointer exception");

//     free(p);

//     return xnil;
// }


// int main(int argc, char ** argv)
// {
//     xeventengine engine = xeventengineinit();
//     return xeventengine_run(&engine);
// }

