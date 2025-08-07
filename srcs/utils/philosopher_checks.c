/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:48:47 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/06 13:59:30 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_eaten_count(t_table *table, int i)
{
	int		eaten;

	pthread_mutex_lock(&table->philos[i]->eat_mutex);
	eaten = table->philos[i]->num_of_times_eaten;
	pthread_mutex_unlock(&table->philos[i]->eat_mutex);
	return (eaten);
}

int	all_philos_ate_enough(t_table *table)
{
	int		i;
	int		eaten;

	if (table->num_of_times_to_eat <= 0)
		return (0);
	i = 0;
	while (i < table->num_of_philos)
	{
		eaten = get_eaten_count(table, i);
		if (eaten < table->num_of_times_to_eat)
			return (0);
		i++;
	}
	return (1);
}

int	check_all_philos_death(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (is_death(table->philos[i]))
			return (1);
		i++;
	}
	return (0);
}
