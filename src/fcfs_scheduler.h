#ifndef __LOG710__FCFS_SCHEDULER__
#define __LOG710__FCFS_SCHEDULER__

#include <stdbool.h>

#include "error.h"
#include "queue.h"
#include "resources.h"

/// FWD: process.h
typedef struct process process_t;

/**
 * @brief Une structure de données contenant toutes les informations pour faire
 * fonctionner un ordonnanceur @e FCFS.
 */
typedef struct fcfs_scheduler
{
    /**
     * @brief La file d'arrivées des processus reçus par cet ordonnanceur.
     */
    queue_t arrivals;
    /**
     * @brief Le processus en cours d'exécution par l'ordonnanceur.
     */
    process_t* current_process;
    /**
     * @brief Les ressources présentement disponibles dans cet ordonnanceur.
     */
    resources_t resources;
} fcfs_scheduler_t;

/**
 * @brief Un fonction permettant d'initialiser les champs de l'ordonnanceur
 * @e FCFS.
 *
 * @param scheduler L'ordonnanceur à initialiser
 * @return Un code d'erreur lors de l'exécution la fonction
 */
error_t fcfs_scheduler_init(fcfs_scheduler_t* scheduler);

/**
 * @brief Libère la mémoire utilisée par l'ordonnanceur.
 *
 * @param scheduler L'ordonnanceur à libérer
 */
void fcfs_scheduler_deinit(fcfs_scheduler_t* scheduler);

/**
 * @brief Ordonnance un nouveau processus dans cet ordonnanceur.
 * @note Cette fonction est exécuté 0 à N fois par quantum.
 *
 * @param scheduler L'ordonanceur
 * @param process Le processus à ordonnancer
 * @return Un code d'erreur
 */
error_t fcfs_scheduler_schedule(fcfs_scheduler_t* scheduler, process_t* process);

/**
 * @brief Indique si l'ordonnanceur a encore des processus à exécuter, présent
 * et futurs.
 *
 * @param scheduler L'ordonnanceur
 * @return Vrai si l'ordonnanceur a du travail, faux autrement.
 */
bool fcfs_scheduler_has_work(const fcfs_scheduler_t* scheduler);

/**
 * @brief Déterminer le processus à exécuter à partir de l'état de
 * l'ordonnanceur pour le quanta courant.
 * @note Cette fonction est exécuté 1 fois par quantum.
 *
 * @param scheduler L'ordonnanceur
 * @return Un code d'erreur
 */
error_t fcfs_scheduler_tick(fcfs_scheduler_t* scheduler);

/**
 * @brief Affiche l'état de l'ordonnanceur.
 *
 * @param scheduler L'ordonnanceur
 */
void fcfs_scheduler_trace(fcfs_scheduler_t* scheduler);

#endif
