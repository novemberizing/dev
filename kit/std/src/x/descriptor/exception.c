#include "exception.h"

extern const xdescriptorexception descriptorexceptioncodes[] = {
    { xexceptioncode_descriptor | xdescriptorexceptioncode_general , "descriptor exception general"},
    { xexceptioncode_descriptor | xdescriptorexceptioncode_close_fail, "descriptor exception close fail" },
    { xexceptioncode_descriptor | xdescriptorexceptioncode_read_return_zero, "descriptor exception read return zero" },
    { xexceptioncode_descriptor | xdescriptorexceptioncode_read_fail, "descriptor exception read fail" },
    { xexceptioncode_descriptor | xdescriptorexceptioncode_write_fail, "descriptor exception write fail" }
};