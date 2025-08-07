/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:15:50 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/06 14:17:09 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*free_philo(t_philo *philo)
{
	pthread_mutex_destroy(&philo->eat_mutex);
	pthread_mutex_destroy(&philo->time_mutex);
	free(philo);
	return (NULL);
}

t_philo	**free_philos(t_philo **philos, int num_of_philos)
{
	int			i;

	i = 0;
	if (!philos)
		return (NULL);
	while (i != num_of_philos)
	{
		if (philos[i])
			free_philo(philos[i]);
		i++;
	}
	free(philos);
	return (NULL);
}
