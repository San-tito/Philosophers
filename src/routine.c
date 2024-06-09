/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/09 02:16:42 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(const char *action, t_philo philo, t_table table)
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
	while (now() < table.start_time)
		philo.last_meal = now();
	while (42)
	{
		pthread_mutex_lock(philo.first_fork);
		log_state("has taken a fork", philo, table);
		pthread_mutex_lock(philo.second_fork);
		log_state("has taken a fork", philo, table);
		log_state("is eating", philo, table);
		philo.last_meal = now();
		ft_sleep(table.time_eat);
		philo.meal_count++;
		pthread_mutex_unlock(philo.first_fork);
		pthread_mutex_unlock(philo.second_fork);
		log_state("is sleeping", philo, table);
		ft_sleep(table.time_sleep);
		log_state("is thinking", philo, table);
	}
	return (0);
}
