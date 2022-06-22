#include "resources.h"

#include <assert.h>
#include <stddef.h>

bool resources_check(const resources_t* available, const resources_t* needed)
{
    assert(available != NULL);
    assert(needed != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return false;
}

void resources_lock(resources_t* available, const resources_t* needed)
{
    assert(available != NULL);
    assert(needed != NULL);
    assert(resources_check(available, needed));

    // TODO(Alexis Brodeur): À implémenter.
}

void resources_unlock(resources_t* available, const resources_t* locked)
{
    assert(available != NULL);
    assert(locked != NULL);

    // TODO(Alexis Brodeur): À implémenter.
}
