#include "error.h"

#include <assert.h>
#include <stddef.h>

static const char* ERROR_NAMES[ERROR_LAST_] = {
    NULL,
    "UNIMPLEMENTED",
    "OUT_OF_MEMORY",
};

const char* error_to_str(error_t error)
{
    assert(error > OK);
    assert(error < ERROR_LAST_);
    return ERROR_NAMES[error];
}
