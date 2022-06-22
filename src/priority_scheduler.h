#ifndef __LOG710__PRIORITY_SCHEDULER__
#define __LOG710__PRIORITY_SCHEDULER__

#include <stdbool.h>

#include "error.h"
#include "queue.h"
#include "resources.h"

#define MAX_PRIORITY 3

/// FWD: process.h
typedef struct process process_t;

/**
 * @brief La structure de données contenant l'information de l'ordonnanceur
 * à multi-niveaux de priorités avec retours.
 *
 */
typedef struct priority_scheduler
{
    /**
     * @brief Les files de prioritées de l'ordonnanceur.
     */
    queue_t priorities[MAX_PRIORITY];
    /**
     * @brief Le processus en cours d'exécution.
     */
    process_t* current_process;
    /**
     * @brief La priorité du processus en cours d'exécution,
     * @note Cette valeur n'a pas d'importance s'il n'y a pas de processus
     * courant.
     */
    size_t current_priority;
    /**
     * @brief Les ressources disponibles dans cet ordonnanceur.
     */
    resources_t resources;
} priority_scheduler_t;

/**
 * @brief Un fonction permettant d'initialiser les champs de l'ordonnanceur
 * multi-niveaux de priorité avec retour.
 *
 * @param scheduler L'ordonnanceur à initialiser
 * @return Un code d'erreur lors de l'exécution la fonction
 */
error_t priority_scheduler_init(priority_scheduler_t* scheduler);

/**
 * @brief Libère la mémoire utilisée par l'ordonnanceur.
 *
 * @param scheduler L'ordonnanceur à libérer
 */
void priority_scheduler_deinit(priority_scheduler_t* scheduler);

/**
 * @brief Ordonnance un nouveau processus dans cet ordonnanceur.
 * @note Cette fonction est exécuté 0 à N fois par quantum.
 *
 * @param scheduler L'ordonanceur
 * @param process Le processus à ordonnancer
 * @return Un code d'erreur
 */
error_t priority_scheduler_schedule(priority_scheduler_t* scheduler, process_t* process);

/**
 * @brief Indique si l'ordonnanceur a encore des processus à exécuter, présent
 * et futurs.
 *
 * @param scheduler L'ordonnanceur
 * @return Vrai si l'ordonnanceur a du travail, faux autrement.
 */
bool priority_scheduler_has_work(const priority_scheduler_t* scheduler);

/**
 * @brief Déterminer le processus à exécuter à partir de l'état de
 * l'ordonnanceur pour le quanta courant.
 * @note Cette fonction est exécuté 1 fois par quantum.
 *
 * @param scheduler L'ordonnanceur
 * @return Un code d'erreur
 */
error_t priority_scheduler_tick(priority_scheduler_t* scheduler);

/**
 * @brief Affiche l'état de l'ordonnanceur.
 *
 * @param scheduler L'ordonnanceur
 */
void priority_scheduler_trace(priority_scheduler_t* scheduler);

#endif
