/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/08 16:57:01 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(const char *action, t_philo philo, t_table table)
{
	pthread_mutex_lock(&table.micro);
	printf("%ld %d %s\n", now() - table.start_time, philo.id, action);
	pthread_mutex_unlock(&table.micro);
}

void	*philosopher(void *arg)
{
	t_philo	philo;
	t_table	table;

	philo = *(t_philo *)arg;
	table = *philo.table;
	while (42)
	{
		pthread_mutex_lock(philo.first_fork);
		log_action("has taken a fork", philo, table);
		pthread_mutex_lock(philo.second_fork);
		log_action("has taken a fork", philo, table);
		log_action("is eating", philo, table);
		ft_sleep(table.time_eat);
		pthread_mutex_unlock(philo.first_fork);
		pthread_mutex_unlock(philo.second_fork);
		log_action("is sleeping", philo, table);
		ft_sleep(table.time_sleep);
		log_action("is thinking", philo, table);
	}
	return (0);
}
