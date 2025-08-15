/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printinfo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:46:47 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/23 13:28:29 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen(s))
		write(fd, &s[i], 1);
}

int	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!is_dead(philo))
	{
		printf("%li	%d %s\n", get_time_in_ms(philo->table),
			philo->id, str);
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (1);
}
