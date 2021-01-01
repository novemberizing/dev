// #include <x/types.h>
// #include <x/log.h>

// #include "_types.h"

// struct xobjint
// {
//     xuint32 flags;
//     destructor rem;
//     xint32 value;
// };

// typedef struct xobjint xobjint;

// static xobj * __check_types_fun_sample_func(xobj * param)
// {
//     xobjint * o = (xobjint *) param;


//     xobjint * result = (xobjint *) xobjnew(sizeof(xobjint), xobj_type_primitive, xnil);
//     result->value = o->value + 64;
//     return (xobj *) result;
// }

// static inline void __check_types_fun_static()
// {

//     xuint32 value = random() % 64;
//     xobjint * param = (xobjint *) xobjnew(sizeof(xobjint), xobj_type_primitive, xnil);
//     param->value = value;

//     xfun o = xfuninit(__check_types_fun_sample_func, (xobj *) param, xnil);

//     xfuncall(&o);
//     xobjint * result = (xobjint *) o.result;
//     xassertion(value + 64 != result->value, "value + 64 != result->value");
//     xfunrem(&o);
// }

// static inline void __check_tyeps_fun_dynamic()
// {
//     xuint32 value = random() % 64;
//     xobjint * param = (xobjint *) xobjnew(sizeof(xobjint), xobj_type_primitive, xnil);
//     param->value = value;

//     xfun * o = xfunnew(xnil, __check_types_fun_sample_func, (xobj *) param, xnil);

//     xfuncall(o);
//     xobjint * result = (xobjint *) o->result;
//     xassertion(value + 64 != result->value, "value + 64 != result->value");
//     xfunrem(o);
// }

// int check_types_fun(int total)
// {
//     for(int i = 0; i < total; i++)
//     {
//         __check_types_fun_static();
//         __check_tyeps_fun_dynamic();
//     }
//     return xtrue;
// }

// int check_types_all(int total)
// {
//     fprintf(stdout, "[check/types] fun => %s\n", check_types_fun(total) ? "ok" : "fail");
//     return xtrue;
// }
