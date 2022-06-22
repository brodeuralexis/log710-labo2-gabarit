#include "./hybrid_scheduler.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "resources.h"

error_t hybrid_scheduler_init(hybrid_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return UNIMPLEMENTED;
}

void hybrid_scheduler_deinit(hybrid_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.
}

error_t hybrid_scheduler_schedule(hybrid_scheduler_t* scheduler, process_t* process)
{
    assert(scheduler != NULL);
    assert(process != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return UNIMPLEMENTED;
}

bool hybrid_scheduler_has_work(const hybrid_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return false;
}

error_t hybrid_scheduler_tick(hybrid_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return UNIMPLEMENTED;
}

static void print_each_process(process_t* process, void* userdata)
{
    resources_t* resources = userdata;

    switch (process->status)
    {
    case SCHEDULED:
        if (process->type == REAL)
        {
            printf("^%zu, ", process->pid);
        }
        else if (resources_check(resources, &process->resources))
        {
            printf("+%zu, ", process->pid);
        }
        else
        {
            printf("-%zu, ", process->pid);
        }

        break;
    case SUSPENDED:
        printf("*%zu, ", process->pid);
        break;
    default:
        fprintf(stderr, "[%s:%d]: unreachable", __FILE__, __LINE__);
        exit(1);
    }
}

void hybrid_scheduler_trace(hybrid_scheduler_t* scheduler)
{
    if (scheduler->current_process != NULL)
    {
        printf("current_process: %zu\n", scheduler->current_process->pid);
        printf("current_priority: %zu\n", scheduler->current_priority);
    }

    for(size_t priority = 0; priority < NUM_HYBRID_PRIORITIES; ++priority)
    {
        printf("priorities[%zu]: ", priority);
        queue_each(&scheduler->priorities[priority], print_each_process, &scheduler->resources);
        printf("\n");
    }
}
