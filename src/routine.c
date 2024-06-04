/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/03 17:54:35 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	philo;
	t_table	table;

	philo = *(t_philo *)arg;
	table = *philo.table;
	while (42)
	{
		pthread_mutex_lock(philo.left_fork);
		printf("%ld %i has taken a fork\n", now() - table.start_time, philo.id);
		pthread_mutex_lock(philo.right_fork);
		printf("%ld %i has taken a fork\n", now() - table.start_time, philo.id);
		printf("%ld %i is eating\n", now() - table.start_time, philo.id);
		ft_sleep(table.time_eat);
		pthread_mutex_unlock(philo.left_fork);
		pthread_mutex_unlock(philo.right_fork);
		printf("%ld %i is sleeping\n", now() - table.start_time, philo.id);
		ft_sleep(table.time_sleep);
		printf("%ld %i is thinking\n", now() - table.start_time, philo.id);
	}
	return (0);
}
