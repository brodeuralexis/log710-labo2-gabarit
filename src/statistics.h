#ifndef __LOG710__STATISTICS__
#define __LOG710__STATISTICS__

#include <stddef.h>

/**
 * @brief Calcule la moyenne cummulative de tous les points de données.
 *
 * @see https://en.wikipedia.org/wiki/Moving_average#Cumulative_average
 * @see https://fr.wikipedia.org/wiki/Moyenne_mobile
 *
 * @param old_average L'ancienne moyenne
 * @param new_value La nouvelle valeur
 * @param new_count Le nouveau nombre d'éléments
 * @return La nouvelle moyenne
 */
double cummulative_average(double old_average, double new_value, size_t new_count);

#endif
