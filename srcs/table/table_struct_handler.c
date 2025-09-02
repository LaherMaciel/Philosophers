/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_struct_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:33:42 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/09/02 17:42:49 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

t_table	*free_table(t_table *table)
{
	int		i;

	if (!table)
		return (NULL);
	if (table->forks)
	{
		i = -1;
		while (++i < table->num_of_philos)
			pthread_mutex_destroy(&table->forks[i]);
		free(table->forks);
	}
	usleep(10000);
	pthread_mutex_destroy(&table->death);
	pthread_mutex_destroy(&table->print_mutex);
	if (table->philosopher)
		free(table->philosopher);
	free(table);
	return (NULL);
}

static t_table	*init_table_values(char **argv, t_table *table)
{
	if (!table->philosopher)
		return (free_table(table));
	table->num_of_philos = ft_atoi(argv[1]);
	if (table->num_of_philos <= 0)
		return (free_table(table));
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die <= 0)
		return (free_table(table));
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat <= 0)
		return (free_table(table));
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep <= 0)
		return (free_table(table));
	if (argv[5] != NULL)
		table->num_of_times_to_eat = ft_atoi(argv[5]);
	else
		table->num_of_times_to_eat = -1;
	table->is_dead = 0;
	table->forks = ft_calloc(sizeof(pthread_mutex_t), table->num_of_philos);
	if (!table->forks)
		return (free_table(table));
	table->start_time = time_in_ms();
	return (table);
}

static int	the_while(long val, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		val = ft_atoi(argv[i]);
		if ((ft_isdigit2(argv[i]) == 0 && val <= 0))
			return (ft_putstr_fd("Error: Argument ", 2),
				ft_putstr_fd(argv[i], 2),
				ft_putstr_fd(" is not a valid positive number.\n", 2), 1);
		if (i == 1 && val > 200)
			return (ft_putstr_fd("Error: Number of philosophers"
					" is greater than 200.\n", 2), 1);
		if (i >= 2 && i != 5 && val < 60)
			return (ft_putstr_fd("Error: Argument ", 2),
				ft_putstr_fd(argv[i], 2),
				ft_putstr_fd(" is less than 60.\n", 2), 1);
		if (i >= 2 && val >= INT_MAX)
			return (ft_putstr_fd("Error: Argument ", 2),
				ft_putstr_fd(argv[i], 2),
				ft_putstr_fd(" exceeds INT_MAX.\n", 2), 1);
	}
	return (0);
}

static t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Error: Invalid number of arguments.\n", 2), NULL);
	if (the_while(0, argv))
		return (NULL);
	table = ft_calloc(sizeof(t_table), 1);
	if (!table)
		return (ft_putstr_fd("Error: Invalid table "
				"initialization.\n", 2), NULL);
	table->philosopher = ft_calloc(sizeof(pthread_t), ft_atoi(argv[1]));
	table = init_table_values(argv, table);
	if (!table)
		return (ft_putstr_fd("Error: Invalid table "
				"initialization.\n", 2), NULL);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->death, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	return (table);
}

t_table	*main_init_table(int argc, char **argv)
{
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (NULL);
	return (table);
}
