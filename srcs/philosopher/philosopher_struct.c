/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:21:48 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/06 14:17:03 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_one_philo(t_table *table)
{
	pthread_mutex_lock(&table->forks[0]);
	printf("0 1 has taken a fork\n");
	usleep(table->time_to_die * 1000);
	printf("%d 1 died\n", table->time_to_die);
	pthread_mutex_unlock(&table->forks[0]);
	return (0);
}

void	join_philos_threads(t_table *table, int numb_of_philos)
{
	int		i;

	i = -1;
	while (++i < numb_of_philos)
		pthread_join(table->philosopher[i], NULL);
}
