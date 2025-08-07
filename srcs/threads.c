/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:09:38 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/07 15:12:38 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death(t_table *table, int i)
{
	pthread_mutex_lock(&table->death);
	if (!table->is_dead)
	{
		pthread_mutex_lock(&table->print_mutex);
		printf("%li %d died\n", time_in_ms() - table->philos[i]->start_time,
			table->philos[i]->id);
		pthread_mutex_unlock(&table->print_mutex);
		table->is_dead = 1;
	}
	pthread_mutex_unlock(&table->death);
	return (NULL);
}

static int	check_philosopher_death(t_table *table)
{
	int		i;
	long	current_time;
	long	last_eaten;

	i = 0;
	while (i < table->num_of_philos)
	{
		current_time = time_in_ms();
		pthread_mutex_lock(&table->philos[i]->eat_mutex);
		last_eaten = table->philos[i]->time_that_eaten;
		pthread_mutex_unlock(&table->philos[i]->eat_mutex);
		if (last_eaten != 0 && (current_time - last_eaten)
			>= table->time_to_die)
			return (i);
		i++;
	}
	return (-1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		dead_philo;

	table = (t_table *)arg;
	while (1)
	{
		dead_philo = check_philosopher_death(table);
		if (dead_philo >= 0)
			return (death(table, dead_philo));
		if (all_philos_ate_enough(table))
		{
			pthread_mutex_lock(&table->death);
			table->is_dead = 1;
			pthread_mutex_unlock(&table->death);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	create_philo_threads(t_philo **philos, t_table *table,
	int numb_of_philos)
{
	int		i;

	i = -1;
	while (++i < numb_of_philos)
	{
		philos[i] = init_philo_values(i, table);
		pthread_create(&table->philosopher[i], NULL,
			routine_loop, (void *)philos[i]);
	}
}

void	threads_handler(t_philo **philos, t_table *table,
	int numb_of_philos)
{
	pthread_t	monitor;

	table->philos = philos;
	create_philo_threads(philos, table, numb_of_philos);
	pthread_create(&monitor, NULL, monitor_routine, (void *)table);
	pthread_join(monitor, NULL);
	usleep(10000);
	join_philos_threads(table, numb_of_philos);
	free_all(philos, table);
}
