#include "priority_scheduler.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "resources.h"
#include "process.h"

error_t priority_scheduler_init(priority_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return UNIMPLEMENTED;
}

void priority_scheduler_deinit(priority_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.
}

error_t priority_scheduler_schedule(priority_scheduler_t* scheduler, process_t* process)
{
    assert(scheduler != NULL);
    assert(process != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return UNIMPLEMENTED;
}

bool priority_scheduler_has_work(const priority_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return false;
}

error_t priority_scheduler_tick(priority_scheduler_t* scheduler)
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
    case READY:
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
    case WAITING:
        printf("*%zu, ", process->pid);
        break;
    default:
        fprintf(stderr, "[%s:%d]: unreachable", __FILE__, __LINE__);
        exit(1);
    }
}

void priority_scheduler_trace(priority_scheduler_t* scheduler)
{
    if (scheduler->current_process != NULL)
    {
        printf("current_process: %zu\n", scheduler->current_process->pid);
        printf("current priority: %zu\n", scheduler->current_priority);
    }

    for (size_t priority = 0; priority < MAX_PRIORITY; ++priority)
    {
        printf("priorities[%zu]: ", priority + 1);
        queue_each(&scheduler->priorities[priority], print_each_process, &scheduler->resources);
        printf("\n");
    }
}
