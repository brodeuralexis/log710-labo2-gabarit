#ifndef __LOG710__ERROR__
#define __LOG710__ERROR__

/**
 * @brief Une énumération de toutes les erreurs qui peuvent survenir dans la
 * simulation.
 * @note En ajoutant un élément dans cette énumération, il faut change
 * @e ERROR_NAMES dans @e error.c
 */
typedef enum error
{
    /**
     * @brief L'absence d'erreur.
     * @note Cette valeur devrait toujours être zéro.
     */
    OK = 0,
    /**
     * @brief Une fonction n'est pas implémentée.
     */
    UNIMPLEMENTED,
    /**
     * @brief Une allocation de mémoire a échouée.
     */
    OUT_OF_MEMORY,
    /**
     * @private
     * @note Ne rien rajouter après cette entrée.
     */
    ERROR_LAST_
} error_t;

/**
 * @brief Donne le nom textuelle d'une erreur à partir du code de l'erreur
 * faisant partit de l'énumération @e error_t.
 *
 * @param error Le code de l'erreur
 * @return Le nom de l'erreur
 */
const char* error_to_str(error_t error);

#endif
