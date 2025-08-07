/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:15:29 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/06 14:21:11 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo_values(int i, t_table *table)
{
	t_philo	*philo;

	philo = ft_calloc(sizeof(t_philo), 1);
	philo->table = table;
	philo->time_multiplier = 1000;
	philo->start_time = time_in_ms();
	philo->time_that_eaten = philo->start_time;
	philo->left_fork = i;
	if (i == table->num_of_philos - 1)
		philo->right_fork = 0;
	else
		philo->right_fork = i + 1;
	philo->is_dead = 0;
	philo->num_of_times_eaten = 0;
	philo->id = i + 1;
	pthread_mutex_init(&philo->eat_mutex, NULL);
	pthread_mutex_init(&philo->time_mutex, NULL);
	return (philo);
}

t_philo	**init_philo(int argc, char **argv)
{
	t_philo	**philos;
	int		num_of_philos;
	int		i;

	philos = NULL;
	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Error: Invalid number of arguments.\n", 2), NULL);
	num_of_philos = ft_atoi(argv[1]);
	if (num_of_philos <= 0)
		return (ft_putstr_fd("Error: Invalid number of "
				"philosophers.\n", 2), NULL);
	i = 0;
	while (argv[++i])
	{
		if (ft_isdigit2(argv[i]) == 0 && ft_atoi(argv[i]) <= 0)
			return (
				ft_putstr_fd("Error: Invalid Argment.\n", 2),
				NULL
			);
	}
	philos = ft_calloc(sizeof(t_philo *), num_of_philos);
	if (!philos)
		return (NULL);
	return (philos);
}

t_philo	**main_init_philos(int argc, char **argv, t_table *table)
{
	t_philo	**philos;

	philos = init_philo(argc, argv);
	if (!philos)
	{
		ft_putstr_fd("Error: Invalid philosopher initialization.\n", 2);
		free_table(table);
		return (NULL);
	}
	return (philos);
}
