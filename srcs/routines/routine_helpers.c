/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:22:50 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/06 15:58:11 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_death(t_philo *philo)
{
	if (!philo || !philo->table)
		return (-1);
	pthread_mutex_lock(&philo->table->death);
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->death);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->death);
	return (0);
}

int	should_break(t_philo *philo, int eaten)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (philo->table->num_of_times_to_eat > 0
		&& eaten >= philo->table->num_of_times_to_eat)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	if (is_death(philo))
		return (1);
	return (0);
}

t_philo	*monitoring(t_philo *philo)
{
	philo->current_time = time_in_ms();
	if (philo->time_that_eaten == 0)
		return (philo);
	if ((philo->current_time - philo->time_that_eaten)
		>= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->death);
		if (!philo->table->is_dead)
		{
			pthread_mutex_lock(&philo->table->print_mutex);
			printf("%li %d died\n", philo->current_time
				- philo->start_time, philo->id);
			pthread_mutex_unlock(&philo->table->print_mutex);
			philo->table->is_dead = 1;
		}
		pthread_mutex_unlock(&philo->table->death);
		return (philo);
	}
	return (philo);
}

/* 
void	precise_sleep(long duration_ms, t_table *table)
{
	long	start;
	//int		dead;

	start = time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&table->death);
		dead = table->is_dead;
		pthread_mutex_unlock(&table->death);
		if (dead || (time_in_ms() - start >= duration_ms))
			break ;
		usleep(100);
	}
}
 */
/* 
t_philo	*precise_sleep(long duration_ms, t_philo *philo)
{
	long	start;

	start = time_in_ms();
	while (1)
	{
		if ((time_in_ms() - start >= duration_ms))
			break ;
		usleep(100);
	}
	philo->current_time = time_in_ms();
	return (philo);
}
 */