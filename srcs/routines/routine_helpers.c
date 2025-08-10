/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:22:50 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/10 11:50:23 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
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
	if (is_dead(philo))
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
		if (!is_dead(philo))
			philo->table->is_dead = 1;
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