#ifndef __LOG710__SCHEDULER__
#define __LOG710__SCHEDULER__

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "error.h"
#include "fcfs_scheduler.h"
#include "hybrid_scheduler.h"
#include "priority_scheduler.h"
#include "process.h"

typedef enum {
    FCFS_SCHEDULER,
    PRIORITY_SCHEDULER,
    HYBRID_SCHEDULER,
    SCHEDULER_TYPE_LAST_,
} scheduler_type_t;

typedef struct scheduler {
    scheduler_type_t type;
    union
    {
        fcfs_scheduler_t        fcfs;
        priority_scheduler_t    priority;
        hybrid_scheduler_t      hybrid;
    };
} scheduler_t;

static inline error_t scheduler_init(scheduler_t* scheduler, scheduler_type_t type)
{
    assert(scheduler != NULL);

    scheduler->type = type;

    switch (scheduler->type)
    {
    case FCFS_SCHEDULER:
        return fcfs_scheduler_init(&scheduler->fcfs);
    case PRIORITY_SCHEDULER:
        return priority_scheduler_init(&scheduler->priority);
    case HYBRID_SCHEDULER:
        return hybrid_scheduler_init(&scheduler->hybrid);
    default:
        assert(false);
        return UNIMPLEMENTED;
    }
}

static inline void scheduler_deinit(scheduler_t* scheduler)
{
    assert(scheduler != NULL);
    assert(scheduler->type >= 0);
    assert(scheduler->type < SCHEDULER_TYPE_LAST_);

    switch (scheduler->type)
    {
    case FCFS_SCHEDULER:
        fcfs_scheduler_deinit(&scheduler->fcfs);
        return;
    case PRIORITY_SCHEDULER:
        priority_scheduler_deinit(&scheduler->priority);
        return;
    case HYBRID_SCHEDULER:
        hybrid_scheduler_deinit(&scheduler->hybrid);
        return;
    default:
        assert(false);
        return;
    }
}

static inline error_t scheduler_schedule(scheduler_t* scheduler, process_t* process)
{
    assert(scheduler != NULL);
    assert(scheduler->type >= 0);
    assert(scheduler->type < SCHEDULER_TYPE_LAST_);

    switch (scheduler->type)
    {
    case FCFS_SCHEDULER:
        return fcfs_scheduler_schedule(&scheduler->fcfs, process);
    case PRIORITY_SCHEDULER:
        return priority_scheduler_schedule(&scheduler->priority, process);
    case HYBRID_SCHEDULER:
        return hybrid_scheduler_schedule(&scheduler->hybrid, process);
    default:
        assert(false);
        return UNIMPLEMENTED;
    }
}

static inline bool scheduler_has_work(const scheduler_t* scheduler)
{
    assert(scheduler != NULL);
    assert(scheduler->type >= 0);
    assert(scheduler->type < SCHEDULER_TYPE_LAST_);

    switch (scheduler->type)
    {
    case FCFS_SCHEDULER:
        return fcfs_scheduler_has_work(&scheduler->fcfs);
    case PRIORITY_SCHEDULER:
        return priority_scheduler_has_work(&scheduler->priority);
    case HYBRID_SCHEDULER:
        return hybrid_scheduler_has_work(&scheduler->hybrid);
    default:
        assert(false);
        return false;
    }
}

static inline error_t scheduler_tick(scheduler_t* scheduler)
{
    assert(scheduler != NULL);
    assert(scheduler->type >= 0);
    assert(scheduler->type < SCHEDULER_TYPE_LAST_);

    switch (scheduler->type)
    {
    case FCFS_SCHEDULER:
        return fcfs_scheduler_tick(&scheduler->fcfs);
    case PRIORITY_SCHEDULER:
        return priority_scheduler_tick(&scheduler->priority);
    case HYBRID_SCHEDULER:
        return hybrid_scheduler_tick(&scheduler->hybrid);
    default:
        assert(false);
        return UNIMPLEMENTED;
    }
}

static inline void scheduler_trace(scheduler_t* scheduler)
{
    assert(scheduler != NULL);
    assert(scheduler->type >= 0);
    assert(scheduler->type < SCHEDULER_TYPE_LAST_);

    switch (scheduler->type)
    {
    case FCFS_SCHEDULER:
        fcfs_scheduler_trace(&scheduler->fcfs);
        return;
    case PRIORITY_SCHEDULER:
        priority_scheduler_trace(&scheduler->priority);
        return;
    case HYBRID_SCHEDULER:
        hybrid_scheduler_trace(&scheduler->hybrid);
        return;
    default:
        assert(false);
        return;
    }
}

#endif
