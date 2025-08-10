/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_rotine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:43:50 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/23 14:15:32 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*think(t_philo *philo)
{
	if (is_dead(philo))
		return (philo);
	philo->current_time = time_in_ms();
	if (print_status(philo, "is thinking"))
		return (philo);
	usleep(800);
	return (philo);
}

static t_philo	*eat(t_philo *philo)
{
	if (is_dead(philo))
		return (philo);
	if (lock_forks(philo))
		return (philo);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->current_time = time_in_ms();
	philo->time_that_eaten = philo->current_time;
	if (print_status(philo, "is eating"))
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		clean_up(philo, 1, 1);
		return (philo);
	}
	philo->num_of_times_eaten++;
	pthread_mutex_unlock(&philo->eat_mutex);
	usleep(philo->table->time_to_eat * 1000);
	clean_up(philo, 1, 1);
	return (philo);
}

static t_philo	*to_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return (philo);
	philo->current_time = time_in_ms();
	if (print_status(philo, "is sleeping"))
		return (philo);
	usleep(philo->table->time_to_sleep * 1000);
	philo->current_time = time_in_ms();
	return (philo);
}

void	*routine_loop(void *arg)
{
	int		eaten;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		eaten = philo->num_of_times_eaten;
		pthread_mutex_unlock(&philo->eat_mutex);
		if (should_break(philo, eaten))
			break ;
		philo = monitoring(philo);
		if (is_dead(philo))
			break ;
		philo = eat(philo);
		if (is_dead(philo))
			break ;
		philo = to_sleep(philo);
		if (is_dead(philo))
			break ;
		philo = think(philo);
		if (is_dead(philo))
			break ;
	}
	return (NULL);
}
