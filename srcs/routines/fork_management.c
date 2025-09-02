/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:30:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/09/02 17:44:20 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_forks_aux(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		return (1);
	}
	philo->current_time = time_in_ms();
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		return (1);
	}
	philo->current_time = time_in_ms();
	print_status(philo, "has taken a fork");
	return (0);
}

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		if (is_dead(philo))
		{
			pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
			return (1);
		}
		philo->current_time = time_in_ms();
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		if (is_dead(philo))
		{
			pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
			return (1);
		}
		philo->current_time = time_in_ms();
		print_status(philo, "has taken a fork");
	}
	else
		return (lock_forks_aux(philo));
	return (0);
}
