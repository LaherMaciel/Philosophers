/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:30:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/06 14:19:04 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_forks_aux(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	if (is_death(philo))
	{
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		return (1);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	if (is_death(philo))
	{
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		return (1);
	}
	print_status(philo, "has taken a fork");
	return (0);
}

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		if (is_death(philo))
		{
			pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
			return (1);
		}
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		if (is_death(philo))
		{
			pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
			return (1);
		}
		print_status(philo, "has taken a fork");
	}
	else
		return (lock_forks_aux(philo));
	return (0);
}
