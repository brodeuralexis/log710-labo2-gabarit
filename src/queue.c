#include "queue.h"

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief La structure de données contenant l'information des noeuds de la file
 * de processus.
 */
struct queue_node
{
    /**
     * @brief Le prochain noeud dans la file de processus.
     */
    queue_node_t* next;
    /**
     * @brief Le processus associé à ce noeud.
     */
    process_t* process;
};

void queue_init(queue_t* queue)
{
    assert(queue != NULL);

    // TODO(Alexis Brodeur): À implémenter.
}

void queue_deinit(queue_t* queue)
{
    assert(queue != NULL);

    // TODO(Alexis Brodeur): À implémenter.
}

bool queue_is_empty(const queue_t* queue)
{
    assert(queue != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return true;
}

error_t queue_enqueue(queue_t* queue, process_t* process)
{
    assert(queue != NULL);
    assert(process != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return UNIMPLEMENTED;
}

process_t* queue_dequeue(queue_t* queue)
{
    assert(queue != NULL);

    // TODO(Alexis Brodeur): À implémenter.

    return NULL;
}

process_t* queue_dequeue_if(queue_t* queue, queue_predicate_t* predicate, void* userdata)
{
    assert(queue != NULL);
    assert(predicate != NULL);

    // TODO(Alexis Brodeur): À implémenter.
    //
    // Inspirez vous de l'implémentation fournie pour `queue_each`.
    ((void) userdata);

    return NULL;
}


void queue_each(const queue_t* queue, queue_each_t* callback, void* userdata)
{
    assert(queue != NULL);
    assert(callback != NULL);

    for (queue_node_t* node = queue->begin; node != NULL; node = node->next)
    {
        callback(node->process, userdata);
    }
}
