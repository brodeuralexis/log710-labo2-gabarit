#include "fcfs_scheduler.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "resources.h"
#include "process.h"

error_t fcfs_scheduler_init(fcfs_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return UNIMPLEMENTED;
}

void fcfs_scheduler_deinit(fcfs_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.
}

error_t fcfs_scheduler_schedule(fcfs_scheduler_t* scheduler, process_t* process)
{
    assert(scheduler != NULL);
    assert(process != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return UNIMPLEMENTED;
}

bool fcfs_scheduler_has_work(const fcfs_scheduler_t* scheduler)
{
    assert(scheduler != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return false;
}

error_t fcfs_scheduler_tick(fcfs_scheduler_t* scheduler)
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


void fcfs_scheduler_trace(fcfs_scheduler_t* scheduler)
{
    if (scheduler->current_process != NULL)
    {
        printf("current_process: %zu\n", scheduler->current_process->pid);
    }

    printf("arrivals: ");
    queue_each(&scheduler->arrivals, print_each_process, NULL);
    printf("\n");
}
