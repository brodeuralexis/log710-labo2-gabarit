#ifndef __LOG710__PROCESS__
#define __LOG710__PROCESS__

#include <stdbool.h>
#include <stddef.h>

#include "resources.h"

/**
 * @brief Une énumération de tous les états de processus possibles dans ce
 * laboratoire.
 */
typedef enum process_status
{
    /**
     * @brief Le processus n'a pas été envoyé à l'ordonnanceur.
     * @note Le processus n'est pas arrivé.
     */
    UNSCHEDULED,
    /**
     * @brief Le processus a été envoyé à l'ordonnanceur.
     */
    SCHEDULED,
    /**
     * @brief Le processus a été démarré par l'ordonnanceur.
     */
    STARTED,
    /**
     * @brief Le processus a terminé de s'exécuter.
     */
    STOPPED,
    /**
     * @brief Le processus a été suspendu par l'ordonnanceur.
     */
    SUSPENDED,
} process_status_t;

/**
 * @brief Le type de processus.
 */
typedef enum process_type
{
    /**
     * @brief Un processus temps-réel.
     */
    REAL = 0,
    /**
     * @brief Un processus utilisateur.
     */
    USER = 1,
} process_type_t;

/**
 * @brief La structure de données contenant l'information d'un processus dans
 * cette simulation.
 */
typedef struct process
{
    /**
     * @brief L'identifier unique du processus.
     * @note Cet identifiant est la ligne dans le fichier.
     */
    size_t pid;
    /**
     * @brief La status du processus.
     * @note La processus est @e UNSCHEDULED par défaut.
     */
    process_status_t status;
    /**
     * @brief Le type de processus.
     * @note Cette valeur provient du fichier.
     */
    process_type_t type;
    /**
     * @brief Le temps d'exécution du processus.
     * @note Cette valeur provient du fichier.
     */
    size_t execution_time;
    /**
     * @brief Le temps d'arrivé du processus.
     * @note Cette valeur provient du fichier.
     */
    size_t arrival_time;
    /**
     * @brief Les ressources nécessaire pour exécuter le processus.
     * @note Ces valeurs proviennent du fichier.
     */
    resources_t resources;

    /**
     * @brief Le temps que le processus a passé à s'exécuter.
     * @note Utiliser le champ @e status pour déterminer si le processus s'est
     * arrêté.
     */
    size_t executed_time;
    /**
     * @brief Le temps d'attente du processus.
     * @note Utiliser cette valeur pour le calcul des temps d'attente moyens.
     */
    size_t waited_time;
} process_t;

/**
 * @brief Initialise l'information du processus à partir de l'information
 * contenue dans la ligne et son numéro de ligne.
 *
 * @param process Le processus
 * @param line Une ligne du ficher
 * @param line_number Le numéro de la ligne du fichier
 */
void process_init_from_line(process_t* process, const char* line, size_t line_number);

/**
 * @brief Change le status du processus à @e SCHEDULED.
 * @note Le processus doit être @e UNSCHEDULED.
 *
 * @param process Le processus
 */
void process_schedule(process_t* process);

/**
 * @brief Change le status du processus à @e STARTED.
 * @note Le processus doit être @e SCHEDULED.
 * @note Il ne doit pas y avoir de processus en cours d'exécution.
 *
 * @param process Le processus
 */
void process_start(process_t* process);

/**
 * @brief Change le status du processs à @e SUSPENDED.
 * @note Le processus doit être @e STARTED.
 * @note Le processus doit être le processus courant.
 *
 * @param process Le processus
 */
void process_suspend(process_t* process);

/**
 * @brief Change le status du processus à @e STARTED.
 * @note Le processus doit être @e SUSPENDED.
 * @note Il ne doit pas y avoir de processus en cours d'exécution.
 *
 * @param process
 */
void process_resume(process_t* process);

/**
 * @brief Avance l'état du processus.
 * @note @e main.c appelle cette fonction.
 *
 * @param process Le processus
 */
void process_tick(process_t* process);

#endif
