/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:58:21 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/06 14:02:24 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo **philos, t_table *table)
{
	int		number_of_philos;

	number_of_philos = table->num_of_philos;
	free_table(table);
	free_philos(philos, number_of_philos);
}

void	clean_up(t_philo *philo, int unlock_left, int unlock_right)
{
	if (unlock_left)
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	if (unlock_right)
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}
