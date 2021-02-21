#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EXCEPTION__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EXCEPTION__H__

#include <x/io.h>

struct xdescriptorexception
{
    xuint32      type;
    const char * message;
};

#define xexceptioncode_descriptor                               (0x01000000u)

#define xdescriptorexceptioncode_general                        (0x00000000u)
#define xdescriptorexceptioncode_close_fail                     (0x00000001u)
#define xdescriptorexceptioncode_read_return_zero               (0x00000002u)
#define xdescriptorexceptioncode_read_fail                      (0x00000003u)
#define xdescriptorexceptioncode_write_fail                     (0x00000004u)
#define xdescriptorexceptioncode_generator_register_fail        (0x00000005u)
#define xdescriptorexceptioncode_generator_dispatch_exception   (0x00000006u)

extern const xdescriptorexception descriptorexceptioncodes[];





#endif // __NOVEMBERIZING_X__DESCRIPTOR__EXCEPTION__H__
