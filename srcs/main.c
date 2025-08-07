/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:30:27 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/06 14:16:02 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	**philos;
	t_table	*table;

	philos = NULL;
	table = NULL;
	table = main_init_table(argc, argv);
	if (!table)
		return (1);
	if (table->num_of_philos == 1)
	{
		handle_one_philo(table);
		free_table(table);
		return (0);
	}
	philos = main_init_philos(argc, argv, table);
	if (!philos)
		return (1);
	threads_handler(philos, table, table->num_of_philos);
	return (0);
}
